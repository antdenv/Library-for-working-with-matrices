TARGET = main.out
TST_TARGET = tests.out

# XXX: Don't forget backslash at the end of any line except the last one
# Main
HDRS = \
	   project/include

SRCS = \
	   project/src/main.c \
	   project/src/init_release_operations.c \
	   project/src/basic_operations.c \
	   project/src/math_operations.c \
	   project/src/extra_operations.c

# Test
TST_HDRS = \
           project/include \
		   project/tests/include

TST_SRCS = \
        project/src/init_release_operations.c \
	   	project/src/basic_operations.c \
	   	project/src/math_operations.c \
	   	project/src/extra_operations.c \
		project/tests/src/*.c

.PHONY: all main test clean

all: main test

main: $(SRCS)
	$(CC) -Wall -Wextra -Werror $(addprefix -I,$(HDRS)) -o $(TARGET) $(CFLAGS) $(SRCS) -lm

test: $(TST_SRCS)
	$(CC) -Wall -Wextra -Werror $(addprefix -I,$(TST_HDRS)) -o $(TST_TARGET) $(CFLAGS) $(TST_SRCS) -lm

clean:
	rm -f $(TARGET) $(TST_TARGET)
