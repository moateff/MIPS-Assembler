CC = gcc
CFLAGS = -Wall -Wextra -g
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
TEST_DIR = test

# Collect all .c files in src/
SRCS = $(wildcard $(SRC_DIR)/*.c)

# Replace src/filename.c -> obj/filename.o
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

TARGET = $(BIN_DIR)/MIPS_Assembler

all: $(TARGET)

# Link objects into binary
$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

# Compile each .c into .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Ensure obj/ and bin/ exist
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Run assembler for all .asm files
run: $(TARGET)
	@for f in $(wildcard $(TEST_DIR)/*.asm); do \
		out=$${f%.asm}.hex; \
		echo "Assembling $$f -> $$out"; \
		$(TARGET) $$f $$out; \
	done
