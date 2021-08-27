# --- Settings

PROJECT_DIR = C:/Users/hasto/Documents/repositories/qnx
QNX632_DIR = C:/QNX632

QCC_LIBS = -lc -lGLES_CM -lgf
QCC_INCS = -I$(PROJECT_DIR)/include -I$(QNX632_DIR)/target/qnx6/usr/include
QCC_CUSTOM_FLAGS = 
QCC_OBJS =	main.o					\
			loaders/bmp_loader.o	\
			models/texture.o		\
			modules/screen.o		\
			utils/debug.o

# ---

QCC_COMPILER = $(QNX632_DIR)/host/win32/x86/usr/bin/qcc

QCC_BUILD_FLAGS = -c -Wc,-Wall -Wc,-Wno-parentheses
QCC_RELEASE_BUILD_FLAGS = -O -DNDEBUG
QCC_DEBUG_BUILD_FLAGS = -g -DVARIANT_g
QCC_X86_BUILD_FLAGS = -Vgcc_ntox86 -DARCH_X86
QCC_SHLE_BUILD_FLAGS = -Vgcc_ntosh -EL -DVARIANT_le -DARCH_SHLE

QCC_LINK_FLAGS = -lang-c++
QCC_RELEASE_LINK_FLAGS = 
QCC_DEBUG_LINK_FLAGS = -g
QCC_X86_LINK_FLAGS = -Vgcc_ntox86
QCC_SHLE_LINK_FLAGS = -Vgcc_ntosh -Wl,--no-keep-memory -EL

QCC_SHLE_LIB_PATHS = -L. -LC:/QNX632/target/qnx6/shle/lib -LC:/QNX632/target/qnx6/shle/usr/lib
QCC_x86_LIB_PATHS = -L. -LC:/QNX632/target/qnx6/x86/lib -LC:/QNX632/target/qnx6/x86/usr/lib

BIN_SHLE_DEBUG = $(PROJECT_DIR)/bin/shle/debug
BIN_SHLE_RELEASE = $(PROJECT_DIR)/bin/shle/release
BIN_X86_DEBUG = $(PROJECT_DIR)/bin/x86/debug
BIN_X86_RELEASE = $(PROJECT_DIR)/bin/x86/release

# ---

all: debug-shle release-shle debug-x86 release-x86

debug-shle: $(QCC_OBJS:=.dbg-shle)
	cd $(BIN_SHLE_DEBUG)   \
		&& $(QCC_COMPILER) $(QCC_LINK_FLAGS) $(QCC_SHLE_LINK_FLAGS) $(QCC_DEBUG_LINK_FLAGS) -o $(BIN_SHLE_DEBUG)/dbg-shle.elf $(QCC_OBJS:=.dbg-shle) $(QCC_SHLE_LIB_PATHS) $(QCC_LIBS) \
		&& rm -f $(QCC_OBJS:=.dbg-shle)

release-shle: $(QCC_OBJS:=.rls-shle)
	cd $(BIN_SHLE_RELEASE) \
		&& $(QCC_COMPILER) $(QCC_LINK_FLAGS) $(QCC_SHLE_LINK_FLAGS) $(QCC_RELEASE_LINK_FLAGS) -o $(BIN_SHLE_RELEASE)/rls-shle.elf $(QCC_OBJS:=.rls-shle) $(QCC_SHLE_LIB_PATHS) $(QCC_LIBS) \
		&& rm -f $(QCC_OBJS:=.rls-shle)

debug-x86: $(QCC_OBJS:=.dbg-x86)
	cd $(BIN_X86_DEBUG)    \
		&& $(QCC_COMPILER) $(QCC_LINK_FLAGS) $(QCC_X86_LINK_FLAGS) $(QCC_DEBUG_LINK_FLAGS) -o $(BIN_X86_DEBUG)/dbg-x86.elf $(QCC_OBJS:=.dbg-x86) $(QCC_x86_LIB_PATHS) $(QCC_LIBS) \
		&& rm -f $(QCC_OBJS:=.dbg-x86)

release-x86: $(QCC_OBJS:=.rls-x86)
	cd $(BIN_X86_RELEASE)  \
		&& $(QCC_COMPILER) $(QCC_LINK_FLAGS) $(QCC_X86_LINK_FLAGS) $(QCC_RELEASE_LINK_FLAGS) -o $(BIN_X86_RELEASE)/rls-x86.elf $(QCC_OBJS:=.rls-x86) $(QCC_x86_LIB_PATHS) $(QCC_LIBS) \
		&& rm -f $(QCC_OBJS:=.rls-x86)

%.o.dbg-shle: %.cc
	$(QCC_COMPILER) $(QCC_INCS) $(QCC_BUILD_FLAGS) $(QCC_SHLE_BUILD_FLAGS) $(QCC_DEBUG_BUILD_FLAGS) $< -o $(BIN_SHLE_DEBUG)/$@

%.o.rls-shle: %.cc
	$(QCC_COMPILER) $(QCC_INCS) $(QCC_BUILD_FLAGS) $(QCC_SHLE_BUILD_FLAGS) $(QCC_RELEASE_BUILD_FLAGS) $< -o $(BIN_SHLE_RELEASE)/$@

%.o.dbg-x86: %.cc
	$(QCC_COMPILER) $(QCC_INCS) $(QCC_BUILD_FLAGS) $(QCC_X86_BUILD_FLAGS) $(QCC_DEBUG_BUILD_FLAGS) $< -o $(BIN_X86_DEBUG)/$@

%.o.rls-x86: %.cc
	$(QCC_COMPILER) $(QCC_INCS) $(QCC_BUILD_FLAGS) $(QCC_X86_BUILD_FLAGS) $(QCC_RELEASE_BUILD_FLAGS) $< -o $(BIN_X86_RELEASE)/$@
