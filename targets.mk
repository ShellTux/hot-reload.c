TARGETS = \
					$(TARGET_DIR)/hot-reload-static \
					$(TARGET_DIR)/libmath.so \
					$(TARGET_DIR)/hot-reload-dynamic \
					$(TARGET_DIR)/hot-reload

DEPS := src/hot-reload-static.c src/math.c
$(TARGET_DIR)/hot-reload-static: $(DEPS:%.c=$(BUILD_DIR)/%.o)
	@mkdir --parents $(shell dirname $@)
	$(CC) -o $@ $^ $(LDFLAGS)

DEPS := src/math.c
$(TARGET_DIR)/libmath.so: $(DEPS:%.c=$(BUILD_DIR)/%.o)
	@mkdir --parents $(shell dirname $@)
	$(CC) -shared -fPIC -o $@ $^ $(LDFLAGS)

DEPS := src/hot-reload-dynamic.c
$(TARGET_DIR)/hot-reload-dynamic: $(DEPS:%.c=$(BUILD_DIR)/%.o)
	@mkdir --parents $(shell dirname $@)
	$(CC) -o $@ $^ $(LDFLAGS) -L$(TARGET_DIR) -lmath

DEPS := src/hot-reload.c
$(TARGET_DIR)/hot-reload: $(DEPS:%.c=$(BUILD_DIR)/%.o)
	@mkdir --parents $(shell dirname $@)
	$(CC) -o $@ $^ $(LDFLAGS)
