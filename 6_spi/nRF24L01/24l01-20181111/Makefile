TARGET := nRF24L01
 
CC := gcc 
 
#注意每行后面不要有空格，否则会算到目录名里面，导致问题
SRC_DIR = src

OBJ_DIR = obj

#这里添加其他头文件路径
INC_DIR = \
	-I./libWiringNP/include/ \
	-I./src/driver \
	-I./src/common \
	-I./src/
	
#这里添加编译参数
CC_FLAGS := $(INC_DIR)  
LNK_FLAGS := \
	-L./libWiringNP/ \
	-lwiringPi -lpthread \
	-Wl,-rpath=./libWiringNP/
 
#这里递归遍历3级子目录
DIRS := $(shell find $(SRC_DIR) -maxdepth 3 -type d)
 
#将每个子目录添加到搜索路径
VPATH = $(DIRS)
 
#查找src_dir下面包含子目录的所有c文件
SOURCES   = $(foreach dir, $(DIRS), $(wildcard $(dir)/*.c))  
OBJS   = $(addprefix $(OBJ_DIR)/,$(patsubst %.c,%.o,$(notdir $(SOURCES))))  

$(TARGET):$(OBJS)
	$(CC) $^ $(LNK_FLAGS) -o $@
#编译之前要创建OBJ目录，确保目录存在
$(OBJ_DIR)/%.o:%.c
	@if [ ! -d $(OBJ_DIR) ]; then mkdir -p $(OBJ_DIR); fi;\
	$(CC) -c $(CC_FLAGS) -o $@ $<

.PHONY : clean
clean:
	rm -rf $(OBJ_DIR) $(TARGET)
