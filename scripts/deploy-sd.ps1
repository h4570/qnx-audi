. ("$($PSScriptRoot)/variables.ps1")
Get-ChildItem -Recurse -Path "$($project_dir)/bin" -Filter $args[0] | Copy-Item -Destination $sd_dir

# Clear logs
"" | Out-File -FilePath "$($sd_dir)/logs/log.txt" 
"" | Out-File -FilePath "$($sd_dir)/logs/stderr.txt" 
"" | Out-File -FilePath "$($sd_dir)/logs/stdout.txt" 