# Developer entry points, thin wrappers around the CMake presets. Requires VCPKG_ROOT, CMake >= 3.24
# and Ninja. `make help` lists the targets.
#
#   make test                                          # all products, Debug (PRESET=dev)
#   make test PRODUCTS="spot"                          # selected products (semicolon or space separated)
#   make test PRESET=release-tests                     # tests of an optimised Release build
#   make test JOBS=8                                   # parallel jobs, for the build and the tests
#   make example NAME=spot/websocket_streams/agg_trade # build one example (incrementally) and run it
#   make format | format-check | lint | lint-fix | asan | install | install-check | docs | clean

PRESET   ?= dev
PRODUCTS ?= all
JOBS     ?=

empty 			:=
space 			:= $(empty) $(empty)
CMAKE_PRODUCTS 	:= $(subst $(space),;,$(strip $(PRODUCTS)))
BUILD_DIR      	:= build/$(PRESET)
IN_GIT_ROOT     = $(filter $(CURDIR),$(shell git rev-parse --show-toplevel 2>/dev/null))
SOURCES         = $(wildcard $(if $(IN_GIT_ROOT), \
	$(shell git ls-files --cached --others --exclude-standard -- '*.cpp' '*.hpp'), \
	$(shell find $(wildcard common clients examples tests) -type f \( -name '*.cpp' -o -name '*.hpp' \))))

.PHONY: help configure build test example asan format format-check lint lint-fix install install-check docs clean

help:
	@awk '/^#/ { sub(/^# ?/, ""); print; next } { exit }' $(firstword $(MAKEFILE_LIST))

configure:
	cmake --preset $(PRESET) -DBINANCE_PRODUCTS="$(CMAKE_PRODUCTS)"

build: configure
	cmake --build --preset $(PRESET) $(if $(JOBS),-j $(JOBS))

test: build
	ctest --preset $(PRESET) $(if $(JOBS),-j $(JOBS))

example:
	@test -n "$(NAME)" || { echo "Usage: make example NAME=<product>/<module>[/<api>]/<name>"; exit 1; }
	@test -f $(BUILD_DIR)/build.ninja || $(MAKE) configure PRODUCTS="$(firstword $(subst /, ,$(NAME)))"
	@cmake --build $(BUILD_DIR) --target examples/$(NAME)
	./$(BUILD_DIR)/examples/$(NAME)

asan:
	$(MAKE) test PRESET=asan PRODUCTS="$(PRODUCTS)"

format:
	clang-format -i $(SOURCES)

format-check:
	clang-format --dry-run --Werror $(SOURCES)

RUN_CLANG_TIDY ?= run-clang-tidy
LINT_SDK = $(if $(filter Darwin,$(shell uname -s)),-extra-arg=-isysroot$(shell xcrun --show-sdk-path 2>/dev/null))

LINT_FILES = '(common|clients/[^/]+)/src/.*\.cpp$$'
LINT_TOOL  = @command -v $(RUN_CLANG_TIDY) >/dev/null || { echo "$(RUN_CLANG_TIDY) not found: install LLVM (see Development in the README), or set RUN_CLANG_TIDY"; exit 1; }

lint: configure
	$(LINT_TOOL)
	$(RUN_CLANG_TIDY) -quiet -p $(BUILD_DIR) $(LINT_SDK) -warnings-as-errors='*' $(LINT_FILES)

lint-fix: configure
	$(LINT_TOOL)
	$(RUN_CLANG_TIDY) -quiet -p $(BUILD_DIR) $(LINT_SDK) -fix -format $(LINT_FILES)

install: build
	rm -rf $(BUILD_DIR)/install
	cmake --install $(BUILD_DIR) --prefix $(BUILD_DIR)/install $(if $(filter release release-tests,$(PRESET)),--strip)

install-check: install
	cmake --fresh -S tests/install -B $(BUILD_DIR)/install-check -G Ninja \
		-DCMAKE_BUILD_TYPE=$$(cmake -L -N $(BUILD_DIR) | sed -n 's/^CMAKE_BUILD_TYPE:STRING=//p') \
		-DCMAKE_TOOLCHAIN_FILE=$(VCPKG_ROOT)/scripts/buildsystems/vcpkg.cmake \
		-DVCPKG_MANIFEST_MODE=OFF \
		-DVCPKG_INSTALLED_DIR=$(CURDIR)/$(BUILD_DIR)/vcpkg_installed \
		-DCMAKE_PREFIX_PATH=$(CURDIR)/$(BUILD_DIR)/install
	cmake --build $(BUILD_DIR)/install-check
	./$(BUILD_DIR)/install-check/install_check

docs:
	mkdir -p docs
	BINANCE_VERSION=$$(jq -r '."version-semver"' vcpkg.json) \
	BINANCE_EXPORT_MACROS="$$(ls clients 2>/dev/null | tr a-z A-Z | sed 's/.*/BINANCE_&_EXPORT=/' | tr '\n' ' ')" \
		doxygen Doxyfile

clean:
	rm -rf build
