
#
# On se base sur la distribution nxtOSEK v210
#
# pour fabriquer des applis temps-reel,
# mais sans passer par le langage oil
# 

# On deduit la liste des objets utilisateur de USR_CFILES
USR_OBJS=$(addsuffix .o, $(addprefix $(BUILD)/, $(notdir $(basename $(USR_CFILES)))))


# Repertoires
nxtOSEK_ROOT=/home/perms/raymond/nxtOSEK
BUILD=./build

# gnu-arm
GNUARM_ROOT=/home/perms/raymond/gnu-arm/4.0.2.lego

CC=$(GNUARM_ROOT)/bin/arm-elf-gcc

CFLAGS= \
         -ffreestanding -fsigned-char -mcpu=arm7tdmi -Os \
         -Winline -Wall -Werror-implicit-function-declaration \
         --param max-inline-insns-single=1000 -mthumb -mthumb-interwork \
         -ffunction-sections -fdata-sections \
         -iquote $(nxtOSEK_ROOT)/lejos_nxj/src//nxtvm/platform/nxt \
         -iquote $(nxtOSEK_ROOT)/lejos_nxj/src//nxtvm/javavm \
         -iquote $(nxtOSEK_ROOT)/ecrobot/bios \
         -iquote $(nxtOSEK_ROOT)/ecrobot \
         -iquote $(nxtOSEK_ROOT)/ecrobot/c \
         -iquote $(nxtOSEK_ROOT)/c++ \

INCLUDES= \
         -I. \
         -I$(USR_PATH) \
         -I$(nxtOSEK_ROOT)/toppers_osek/kernel \
         -I$(nxtOSEK_ROOT)/toppers_osek/include \
         -I$(nxtOSEK_ROOT)/toppers_osek/config/at91sam7s-gnu \
         -I$(nxtOSEK_ROOT)/toppers_osek/config/at91sam7s-gnu/lego_nxt \
         -I$(nxtOSEK_ROOT)/toppers_osek/sg \
         -I$(nxtOSEK_ROOT)/toppers_osek/syslib/at91sam7s-gnu/lego_nxt  \

AS = $(GNUARM_ROOT)/bin/arm-elf-as

ASFLAGS= \
	-mcpu=arm7tdmi \
	-mthumb-interwork \


LD=$(GNUARM_ROOT)/bin/arm-elf-g++

LFLAGS= \
   -mthumb \
   -mthumb-interwork \


LIBS= \
 -L \
 -L$(USR_PATH) \
 -L$(nxtOSEK_ROOT)/lejos_nxj/src//nxtvm/platform/nxt \
 -L$(nxtOSEK_ROOT)/lejos_nxj/src//nxtvm/javavm \
 -L$(nxtOSEK_ROOT)/ecrobot/bios \
 -L$(nxtOSEK_ROOT)/ecrobot \
 -L$(nxtOSEK_ROOT)/ecrobot/c \
 -L$(nxtOSEK_ROOT)/c++ \
 -L$(BUILD) \
 -lm \
 -llejososek \
 -lecrobot \

OCOPY=$(GNUARM_ROOT)/bin/arm-elf-objcopy

# Pour simplifier les regles, les répertoires source nxtOSEK

VPATH=\
$(nxtOSEK_ROOT)/toppers_osek/kernel:\
$(nxtOSEK_ROOT)/toppers_osek/config/at91sam7s-gnu:\
$(nxtOSEK_ROOT)/toppers_osek/config/at91sam7s-gnu/lego_nxt:\
$(nxtOSEK_ROOT)/toppers_osek/syslib/at91sam7s-gnu/lego_nxt:\
$(nxtOSEK_ROOT)/ecrobot/c:\
$(nxtOSEK_ROOT)/lejos_nxj/src/nxtvm/platform/nxt:\

# REGLE 
all: doall

# OBJETS kernel
OBJS= \
  $(BUILD)/alarm.o \
  $(BUILD)/event.o \
  $(BUILD)/interrupt.o \
  $(BUILD)/osctl.o \
  $(BUILD)/resource.o \
  $(BUILD)/task.o \
  $(BUILD)/task_manage.o \
  $(BUILD)/cpu_config.o \
  $(BUILD)/sys_config.o \
  $(BUILD)/kernel_cfg.o \
  $(BUILD)/syscalls.o \
  $(BUILD)/ecrobot_bluetooth.o \
  $(BUILD)/ecrobot_base.o \
  $(BUILD)/ecrobot.o \
  $(USR_OBJS) \
  $(BUILD)/hw_sys_timer.oram \
  $(BUILD)/vectors.o \
  $(BUILD)/debug.o \
  $(BUILD)/sys_support.o \
  $(BUILD)/nxt_binary_header.o \
  $(BUILD)/nxt_entry_point.o \
  $(BUILD)/ecrobot_init.o \
  $(BUILD)/cpu_support.o \
  $(BUILD)/irq.oram \


$(BUILD)/%.o : %.c
	$(CC) -c $(CFLAGS) $(INCLUDES) -std=gnu99 -c -MD -o $@ $<

$(BUILD)/%.oram : %.c
	$(CC) -c $(CFLAGS) $(INCLUDES) -std=gnu99 -c -MD -o $@ $<
	
$(BUILD)/%.o : %.s
	$(AS) $(ASFLAGS) $(INCLUDES) -o $@ $<

$(BUILD)/%.o : %.S
	$(CC) $(ASFLAGS) $(INCLUDES) -c -o $@ $<

$(BUILD)/%.oram : %.s
	$(CC) $(ASFLAGS) $(INCLUDES) -c -o $@ $<

#
# Edition de lien 
# sous nxtOSEK, on fabrique en standard 3 versions exécutables
#  .rom  : pour un chargement en rom
#  .ram  : pour un chargement en ram (voir fwexe)
#  .rxe  : ??? 
# Normalement, on se sert du ram
#
# La méthode est similaire dans les 3 cas :
#
# - on extrait à coup de sed une table de load (.ld) 
#   à partir d'une table commune
#   bizare : pourqoui pas l'avoir définie une bonne fois pour toute ??
# 
# - on linke les objets/librairies sous cette table pour obtenir un .elf
# - on génère l'exécutable par bincopy du .elf 


# Version .rom
$(BUILD)/$(TARGET)_rom.ld : $(nxtOSEK_ROOT)/ecrobot/c/sam7_ecrobot.lds
	sed -e 's/^ROM_ONLY//' -e '/^RAM_ONLY/d' -e '/^RXE_ONLY/d' $< > $@

# Version .ram
$(BUILD)/$(TARGET)_ram.ld : $(nxtOSEK_ROOT)/ecrobot/c/sam7_ecrobot.lds
	sed -e 's/^RAM_ONLY//' -e '/^ROM_ONLY/d' -e '/^RXE_ONLY/d' $< > $@

# Version .rxe
$(BUILD)/$(TARGET)_rxe.ld : $(nxtOSEK_ROOT)/ecrobot/c/sam7_ecrobot.lds
	sed -e 's/^RXE_ONLY//' -e '/^RAM_ONLY/d' -e '/^ROM_ONLY/d' $< > $@

%.elf : $(OBJS) $(BUILD)/%.ld
	$(LD) -nostartfiles -o $@ $(OBJS) -T $(BUILD)/$*.ld $(LFLAGS) \
        -Wl,--allow-multiple-definition \
        -Wl,-Map,$*.map \
        -Wl,--cref \
        -Wl,--gc-sections \
        $(LIBS) 

# obj copy ...

%.bin : %.elf
	$(OCOPY) -O binary $< $@
 
%.rxe : %_rxe.elf
	$(OCOPY) -O binary $< $@


#-------------------------------------------------
$(BUILD):
	mkdir -p $(BUILD)

doall: $(BUILD) $(TARGET)_rom.bin $(TARGET)_ram.bin $(TARGET).rxe


clean:
	rm -f $(BUILD)/* $(TARGET)_*.bin $(TARGET).rxe $(TARGET)_*.elf $(TARGET)_*.map
