NAME = Spencer
DIR = .
PORT = /dev/ttyUSB0

ACLI = /home/cm/.arduino/arduino-cli

srcFiles = $(shell find $(DIR)/src/ -name '*.cpp') $(shell find $(DIR)/ src/ -name '*.cpp')
headerFiles = $(shell find $(DIR)/src/ -name '*.h') $(shell find $(DIR)/src/ -name '*.hpp')

.PHONY: upload clean

build: $(DIR)/build/$(NAME).bin

$(DIR)/build/$(NAME).bin: $(srcFiles) $(headerFiles) $(DIR)/$(NAME).ino
	@mkdir -p $(DIR)/build
	cd $(DIR); \
	$(ACLI) compile --fqbn esp8266:esp8266:nodemcu -o build/$(NAME).bin $(NAME).ino

upload: | $(DIR)/build/$(NAME).bin
	@cd $(DIR); \
	$(ACLI) upload --fqbn esp8266:esp8266:nodemcu -p $(PORT) -i build/$(NAME).bin

clean:
	cd $(DIR); \
	rm -rf build

