SRC = src
OBJ = obj
BIN = bin/stog
CC  = clang 
CXX = clang++
CFLAGS = -Wall
#CXXFLAGS = -Wall
LIBS = -pthread -lrt -ldl

rwildcard = $(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) \
$(filter $(subst *,%,$2),$d))
DEPS = $(call rwildcard,src,*.h)
SRCS = $(call rwildcard,src,*.cpp)
SRCC = $(call rwildcard,src,*.c)
OBJS = $(SRCS:.cpp=.o)
OBJC = $(SRCC:.c=.o)


all: $(BIN)

release: CFLAGS = -Wall -O2
release: $(BIN)

debug: CFLAGS= -Wall -DLOG_USE_COLOR -DDEBUG -g
debug: $(BIN)

target: CFLAGS = -Wall -DUSING_TOOLCHAIN
target: $(BIN)

%.o: %.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CFLAGS)

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(BIN): $(OBJS) $(OBJC)
	$(CXX) $(CFLAGS) $(LIBS) $^ -o $@

install: $(BIN)
	mkdir /etc/stog
	mkdir /var/lib/stog
	mkdir /var/log/stog
	cp resources/stog.ini /etc/stog/config.ini
	cp resources/stog.service /etc/systemd/system/
	cp $(BIN) /usr/bin/
	#cp resources/stog.db /var/lib/stog/stog.db
	systemctl daemon-reload
	systemctl start stog.service
	systemctl enable stog.service

uninstall:
	systemctl stop stog.service
	systemctl disable stog.service
	rm -f /etc/stog.ini /etc/systemd/system/stog.service
	rm -f /usr/bin/stog
	rm -rf /var/lib/stog
	rm -rf /var/log/stog
	systemctl daemon-reload

clean:
	rm -f $(OBJS) $(OBJC) $(CLIENT_BIN) $(BIN)

