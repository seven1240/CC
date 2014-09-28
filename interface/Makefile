include Makefile.rule

OUTPUT_PATH=./output/
THIRD_PATH=./third/

modules=acd ims ivr ap
third-modules=json-cpp

all:
	@for mod in $(modules);\
	do\
		make -C $$mod/bidl/ clean;\
		make -C $$mod/bidl/ ;\
		if [ ! -d $(OUTPUT_PATH)/$$mod/include ]; then mkdir -p $(OUTPUT_PATH)/$$mod/include; fi ; \
		cp -r $$mod/bidl/*.h $(OUTPUT_PATH)/$$mod/include/ ;\
		if [ ! -d $(OUTPUT_PATH)/$$mod/lib/linux ]; then mkdir -p $(OUTPUT_PATH)/$$mod/lib/linux; fi ; \
		cp -r $$mod/bidl/*.a* $(OUTPUT_PATH)/$$mod/lib/linux/ ; \
		if [ ! -d $(OUTPUT_PATH)/$$mod/api ]; then mkdir -p $(OUTPUT_PATH)/$$mod/api; fi ; \
		cp -r $$mod/bidl/*.bidl $(OUTPUT_PATH)/$$mod/api/ ;\
	done

	@for mod in $(THIRD_PATH)/$(third-modules);\
	do\
		make -C $$mod/ clean; \
		make -C $$mod/ ;\
		if [ ! -d $(OUTPUT_PATH)/$$mod/include ]; then mkdir -p $(OUTPUT_PATH)/$$mod/include; fi ; \
		cp -r $$mod/include/json/* $(OUTPUT_PATH)/$$mod/include/ ;\
		if [ ! -d $(OUTPUT_PATH)/$$mod/lib/linux ]; then mkdir -p $(OUTPUT_PATH)/$$mod/lib/linux; fi ; \
		cp -r $$mod/*.a* $(OUTPUT_PATH)/$$mod/lib/linux/ ;\
	done

	@cp -r $(BGCC_DIR) $(OUTPUT_PATH)/bgcc

clean:
	@for mod in $(modules);\
	do\
		make -C $$mod/bidl/ clean ;\
	done
	
	@for mod in $(THIRD_PATH)/$(third-modules);\
	do\
		make -C $$mod/ clean;\
	done

	@rm -fr output


