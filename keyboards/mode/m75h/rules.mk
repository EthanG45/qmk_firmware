# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = yes     # Enable Bootmagic Lite
MOUSEKEY_ENABLE = no       # Mouse keys
EXTRAKEY_ENABLE = yes      # Audio control and System control
CONSOLE_ENABLE = no        # Console for debug
COMMAND_ENABLE = no        # Commands for debug and configuration
NKRO_ENABLE = yes          # Enable N-Key Rollover
BACKLIGHT_ENABLE = no      # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = no       # Enable keyboard RGB underglow
AUDIO_ENABLE = no          # Audio output
LTO_ENABLE = yes
APPLE_FN_ENABLE = yes       # Enable Apple Fn key functionality

# Enter lower-power sleep mode when on the ChibiOS idle thread
OPT_DEFS += -DCORTEX_ENABLE_WFI_IDLE=TRUE -DDEBUG_EEPROM_OUTPUT=TRUE
