/*
 * $QNXLicenseC:
 * Copyright 2007, QNX Software Systems. All Rights Reserved.
 * 
 * You must obtain a written license from and pay applicable license fees to QNX 
 * Software Systems before you may reproduce, modify or distribute this software, 
 * or any work that includes all or part of this software.   Free development 
 * licenses are available for evaluation and non-commercial purposes.  For more 
 * information visit http://licensing.qnx.com or email licensing@qnx.com.
 *  
 * This file may contain contributions from others.  Please review this entire 
 * file for other proprietary rights or license notices, as well as the QNX 
 * Development Suite License Guide at http://licensing.qnx.com/license-guide/ 
 * for other information.
 * $
 */

// DODAĆ  -lasound

#include <errno.h>
#include <fcntl.h>
#include <gulliver.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/select.h>
#include <sys/stat.h>
#include <sys/termio.h>
#include <sys/types.h>
#include <unistd.h>

#include <sys/asoundlib.h>

int max(int a, int b)
{
  return a > b ? a : b;
}

int min(int a, int b)
{
  return a < b ? a : b;
}

const char *kRiffId = "RIFF";
const char *kWaveId = "WAVE";

typedef struct
{
  char tag[4];
  long length;
} RiffTag;

typedef struct
{
  char Riff[4];
  long Size;
  char Wave[4];
} RiffHdr;

typedef struct
{
  short FormatTag;
  short Channels;
  long SamplesPerSec;
  long AvgBytesPerSec;
  short BlockAlign;
  short BitsPerSample;
} WaveHdr;

int err(char *msg)
{
  perror(msg);
  return -1;
}

int FindTag(FILE *fp, const char *tag)
{
  int retVal;
  RiffTag tagBfr = {"", 0};

  retVal = 0;

  // Keep reading until we find the tag or hit the EOF.
  while (fread((unsigned char *)&tagBfr, sizeof(tagBfr), 1, fp))
  {

    // If this is our tag, set the length and break.
    if (strncmp(tag, tagBfr.tag, sizeof tagBfr.tag) == 0)
    {
      retVal = ENDIAN_LE32(tagBfr.length);
      break;
    }

    // Skip ahead the specified number of bytes in the stream
    fseek(fp, tagBfr.length, SEEK_CUR);
  }

  // Return the result of our operation
  return (retVal);
}

int CheckHdr(FILE *fp)
{
  RiffHdr riffHdr = {"", 0};

  // Read the header and, if successful, play the file
  // file or WAVE file.
  if (fread((unsigned char *)&riffHdr, sizeof(RiffHdr), 1, fp) == 0)
    return 0;

  if (strncmp(riffHdr.Riff, kRiffId, strlen(kRiffId)) ||
      strncmp(riffHdr.Wave, kWaveId, strlen(kWaveId)))
    return -1;

  return 0;
}

int dev_raw(int fd)
{
  struct termios termios_p;

  if (tcgetattr(fd, &termios_p))
    return (-1);

  termios_p.c_cc[VMIN] = 1;
  termios_p.c_cc[VTIME] = 0;
  termios_p.c_lflag &= ~(ECHO | ICANON | ISIG | ECHOE | ECHOK | ECHONL);
  termios_p.c_oflag &= ~(OPOST);
  return (tcsetattr(fd, TCSANOW, &termios_p));
}

int dev_unraw(int fd)
{
  struct termios termios_p;

  if (tcgetattr(fd, &termios_p))
    return (-1);

  termios_p.c_lflag |= (ECHO | ICANON | ISIG | ECHOE | ECHOK | ECHONL);
  termios_p.c_oflag |= (OPOST);
  return (tcsetattr(fd, TCSAFLUSH, &termios_p));
}

//*****************************************************************************
/* *INDENT-OFF* */
#ifdef __USAGE
% C[Options] *

    Options : -a [card #:]<dev #> the card &device number to play out on
#endif
              /* *INDENT-ON* */
              //*****************************************************************************

              int
              main(int argc, char **argv)
{
  int card = -1;
  int dev = 0;
  snd_pcm_t *pcm_handle;
  FILE *file1;
  WaveHdr wavHdr1;
  int mSamples;
  int mSampleRate;
  int mSampleChannels;
  int mSampleBits;
  char *mSampleBfr1;
  int fragsize = -1;
  int verbose = 0;

  int rtn;
  snd_pcm_channel_info_t pi;
  snd_mixer_t *mixer_handle;
  snd_mixer_group_t group;
  snd_pcm_channel_params_t pp;
  snd_pcm_channel_setup_t setup;
  int bsize, n, N = 0, c;
  fd_set rfds, wfds;

  while ((c = getopt(argc, argv, "a:f:v")) != EOF)
  {
    switch (c)
    {
    case 'a':
      if (strchr(optarg, ':'))
      {
        card = atoi(optarg);
        dev = atoi(strchr(optarg, ':') + 1);
      }
      else
        dev = atoi(optarg);
      printf("Using card %d device %d \n", card, dev);
      break;
    case 'f':
      fragsize = atoi(optarg);
      break;
    case 'v':
      verbose = 1;
      break;
    default:
      return 1;
    }
  }

#define DEVICE_NAME "/dev/snd/navi"

  setvbuf(stdin, NULL, _IONBF, 0);

  // na tych jest blad
  // if ((rtn = snd_pcm_open_name(&pcm_handle, "SDS", SND_PCM_OPEN_PLAYBACK)) < 0)
  // if ((rtn = snd_pcm_open_name(&pcm_handle, "NAD", SND_PCM_OPEN_PLAYBACK)) < 0)
  // if ((rtn = snd_pcm_open_name(&pcm_handle, "BT-Tr", SND_PCM_OPEN_PLAYBACK)) < 0)
  // if ((rtn = snd_pcm_open_name(&pcm_handle, "tones1", SND_PCM_OPEN_PLAYBACK)) < 0)
  // if ((rtn = snd_pcm_open_name(&pcm_handle, "ent3", SND_PCM_OPEN_PLAYBACK)) < 0)
  // if ((rtn = snd_pcm_open_name(&pcm_handle, "MicINRefBTNad", SND_PCM_OPEN_PLAYBACK)) < 0)

  if ((rtn = snd_pcm_open_name(&pcm_handle, DEVICE_NAME, SND_PCM_OPEN_PLAYBACK)) < 0)
    return err("device open");

  // Hmmm urządzenia grają ale nic nie slychac. nie jestem w stanie polaczyc sie do zadnego miksera

  // if (card == -1)
  // {
  // if ((rtn = snd_pcm_open_preferred(&pcm_handle, &card, &dev, SND_PCM_OPEN_PLAYBACK)) < 0)
  //     return err("device open");
  // }
  // else
  // {
  //   if ((rtn = snd_pcm_open(&pcm_handle, card, dev, SND_PCM_OPEN_PLAYBACK)) < 0)
  //     return err("device open");
  // }

  if (argc < 2)
    return err("no file specified");

  if ((file1 = fopen(argv[optind], "r")) == 0)
    return err("file open #1");

  if (CheckHdr(file1) == -1)
    return err("CheckHdr #1");

  mSamples = FindTag(file1, "fmt ");
  fread(&wavHdr1, sizeof(wavHdr1), 1, file1);
  fseek(file1, (mSamples - sizeof(WaveHdr)), SEEK_CUR);

  mSampleRate = ENDIAN_LE32(wavHdr1.SamplesPerSec);
  mSampleChannels = ENDIAN_LE16(wavHdr1.Channels);
  mSampleBits = ENDIAN_LE16(wavHdr1.BitsPerSample);

  printf("SampleRate = %d, Channels = %d, SampleBits = %d\n", mSampleRate, mSampleChannels,
         mSampleBits);

  /* disabling mmap is not actually required in this example but it is included to 
     * demonstrate how it is used when it is required.
     */
  if ((rtn = snd_pcm_plugin_set_disable(pcm_handle, PLUGIN_DISABLE_MMAP)) < 0)
  {
    fprintf(stderr, "snd_pcm_plugin_set_disable failed: %s\n", snd_strerror(rtn));
    return -1;
  }

  memset(&pi, 0, sizeof(pi));
  pi.channel = SND_PCM_CHANNEL_PLAYBACK;
  if ((rtn = snd_pcm_plugin_info(pcm_handle, &pi)) < 0)
  {
    fprintf(stderr, "snd_pcm_plugin_info failed: %s\n", snd_strerror(rtn));
    return -1;
  }

  memset(&pp, 0, sizeof(pp));

  pp.mode = SND_PCM_MODE_BLOCK;
  pp.channel = SND_PCM_CHANNEL_PLAYBACK;
  pp.start_mode = SND_PCM_START_FULL;
  pp.stop_mode = SND_PCM_STOP_STOP;

  pp.buf.block.frag_size = pi.max_fragment_size;
  if (fragsize != -1)
    pp.buf.block.frag_size = fragsize;
  pp.buf.block.frags_max = 1;
  pp.buf.block.frags_min = 1;

  pp.format.interleave = 1;
  pp.format.rate = mSampleRate;
  pp.format.voices = mSampleChannels;

  if (ENDIAN_LE16(wavHdr1.FormatTag) == 6)
    pp.format.format = SND_PCM_SFMT_A_LAW;
  else if (ENDIAN_LE16(wavHdr1.FormatTag) == 7)
    pp.format.format = SND_PCM_SFMT_MU_LAW;
  else if (mSampleBits == 8)
    pp.format.format = SND_PCM_SFMT_U8;
  else if (mSampleBits == 24)
    pp.format.format = SND_PCM_SFMT_S24;
  else
    pp.format.format = SND_PCM_SFMT_S16_LE;

  if ((rtn = snd_pcm_plugin_params(pcm_handle, &pp)) < 0)
  {
    fprintf(stderr, "snd_pcm_plugin_params failed: %s\n", snd_strerror(rtn));
    return -1;
  }

  if ((rtn = snd_pcm_plugin_prepare(pcm_handle, SND_PCM_CHANNEL_PLAYBACK)) < 0)
    fprintf(stderr, "snd_pcm_plugin_prepare failed: %s\n", snd_strerror(rtn));

  memset(&setup, 0, sizeof(setup));
  memset(&group, 0, sizeof(group));
  setup.channel = SND_PCM_CHANNEL_PLAYBACK;
  setup.mixer_gid = &group.gid;
  if ((rtn = snd_pcm_plugin_setup(pcm_handle, &setup)) < 0)
  {
    fprintf(stderr, "snd_pcm_plugin_setup failed: %s\n", snd_strerror(rtn));
    return -1;
  }
  printf("Format %s \n", snd_pcm_get_format_name(setup.format.format));
  printf("Frag Size %d \n", setup.buf.block.frag_size);
  printf("Rate %d \n", setup.format.rate);
  bsize = setup.buf.block.frag_size;

  if (group.gid.name[0] == 0)
  {
    printf("Mixer Pcm Group [%s] Not Set \n", group.gid.name);
    exit(-1);
  }
  printf("Mixer Pcm Group [%s]\n", group.gid.name);
  if ((rtn = snd_mixer_open_name(&mixer_handle, "/dev/snd/mixerC0D0")) < 0)
  {
    fprintf(stderr, "snd_mixer_open failed: %s\n", snd_strerror(rtn));
    return -1;
  }

  mSamples = FindTag(file1, "data");

  mSampleBfr1 = (char *)malloc(bsize);
  FD_ZERO(&rfds);
  FD_ZERO(&wfds);
  n = 1;
  while (N < mSamples && n > 0)
  {
    if (tcgetpgrp(0) == getpid())
      FD_SET(STDIN_FILENO, &rfds);
    FD_SET(snd_mixer_file_descriptor(mixer_handle), &rfds);
    FD_SET(snd_pcm_file_descriptor(pcm_handle, SND_PCM_CHANNEL_PLAYBACK), &wfds);

    rtn = max(snd_mixer_file_descriptor(mixer_handle),
              snd_pcm_file_descriptor(pcm_handle, SND_PCM_CHANNEL_PLAYBACK));

    if (select(rtn + 1, &rfds, &wfds, NULL, NULL) == -1)
      return err("select");

    if ((rtn = snd_mixer_group_read(mixer_handle, &group)) < 0)
      fprintf(stderr, "snd_mixer_group_read failed: %s\n", snd_strerror(rtn));
    // group.volume.names.front_left = 30;
    // group.volume.names.front_right = 30;

    if (FD_ISSET(STDIN_FILENO, &rfds))
    {

      dev_raw(fileno(stdin));
      c = getc(stdin);
      dev_unraw(fileno(stdin));

      if (c != EOF)
      {
        switch (c)
        {
        case 'q':
          group.volume.names.front_left += 10;
          break;
        case 'a':
          group.volume.names.front_left -= 10;
          break;
        case 'w':
          group.volume.names.front_left += 10;
          group.volume.names.front_right += 10;
          break;
        case 's':
          group.volume.names.front_left -= 10;
          group.volume.names.front_right -= 10;
          break;
        case 'e':
          group.volume.names.front_right += 10;
          break;
        case 'd':
          group.volume.names.front_right -= 10;
          break;
        }
        if (group.volume.names.front_left > group.max)
          group.volume.names.front_left = group.max;
        if (group.volume.names.front_left < group.min)
          group.volume.names.front_left = group.min;
        if (group.volume.names.front_right > group.max)
          group.volume.names.front_right = group.max;
        if (group.volume.names.front_right < group.min)
          group.volume.names.front_right = group.min;
      }
      else
        exit(0);
    }
    // if ((rtn = snd_mixer_group_write(mixer_handle, &group)) < 0)
    //   fprintf(stderr, "snd_mixer_group_write failed: %s\n", snd_strerror(rtn));
    printf("Volume Now at %d:%d \n",
           100 * (group.volume.names.front_left - group.min) / (group.max - group.min),
           100 * (group.volume.names.front_right - group.min) / (group.max - group.min));

    if (FD_ISSET(snd_mixer_file_descriptor(mixer_handle), &rfds))
    {
      snd_mixer_callbacks_t callbacks = {0, 0, 0, 0};

      snd_mixer_read(mixer_handle, &callbacks);
    }

    if (FD_ISSET(snd_pcm_file_descriptor(pcm_handle, SND_PCM_CHANNEL_PLAYBACK), &wfds))
    {
      snd_pcm_channel_status_t status;
      int written = 0;

      if ((n = fread(mSampleBfr1, 1, min(mSamples - N, bsize), file1)) <= 0)
        continue;
      written = snd_pcm_plugin_write(pcm_handle, mSampleBfr1, n);
      if (verbose)
        printf("bytes written = %d \n", written);
      if (written < n)
      {
        memset(&status, 0, sizeof(status));
        status.channel = SND_PCM_CHANNEL_PLAYBACK;
        if (snd_pcm_plugin_status(pcm_handle, &status) < 0)
        {
          fprintf(stderr, "underrun: playback channel status error\n");
          exit(1);
        }

        if (status.status == SND_PCM_STATUS_READY ||
            status.status == SND_PCM_STATUS_UNDERRUN)
        {
          if (snd_pcm_plugin_prepare(pcm_handle, SND_PCM_CHANNEL_PLAYBACK) < 0)
          {
            fprintf(stderr, "underrun: playback channel prepare error\n");
            exit(1);
          }
        }
        if (written < 0)
          written = 0;
        written += snd_pcm_plugin_write(pcm_handle, mSampleBfr1 + written, n - written);
      }
      N += written;
    }
  }

  n = snd_pcm_plugin_flush(pcm_handle, SND_PCM_CHANNEL_PLAYBACK);

  rtn = snd_mixer_close(mixer_handle);
  rtn = snd_pcm_close(pcm_handle);
  fclose(file1);
  return (0);
}