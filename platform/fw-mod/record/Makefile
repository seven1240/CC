MOD_NAME = mod_ccl_record
MOD_CONF = ccl_record

WORKROOT=../../../../../
FS_MOD_SRC=$(WORKROOT)thirdsrc/freeswitch/freeswitch-1.0.6/src/mod/

OUTPUT_PATH=./output/

all:
	cp -r $(MOD_NAME) $(FS_MOD_SRC)/applications/
	make -C $(FS_MOD_SRC)/applications/$(MOD_NAME)/
	if [ ! -d $(OUTPUT_PATH) ]; then mkdir -p $(OUTPUT_PATH); fi
	cp $(FS_MOD_SRC)/applications/$(MOD_NAME)/.libs/$(MOD_NAME).so $(OUTPUT_PATH)/
	cp $(MOD_NAME)/conf/$(MOD_CONF).conf.xml $(OUTPUT_PATH)/

clean:
	if [ -d $(FS_MOD_SRC)/applications/$(MOD_NAME)/ ]; then make -C $(FS_MOD_SRC)/applications/$(MOD_NAME)/ clean; fi
	if [ -d $(FS_MOD_SRC)/applications/$(MOD_NAME)/ ]; then rm -fr $(FS_MOD_SRC)/applications/$(MOD_NAME)/; fi
	if [ -d $(OUTPUT_PATH) ]; then rm -fr $(OUTPUT_PATH); fi
