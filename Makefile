CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
TRANSLATOR = bf2cpp
EXAMPLES_DIR = examples
SOURCES = brainfuck.cpp

# Default target
all: bf2cpp convert examples

# Compile the translator
bf2cpp: bf2cpp.cpp
	$(CXX) $(CXXFLAGS) bf2cpp.cpp -o $(TRANSLATOR)

# Convert all .bf files in examples directory to .cpp files
convert: bf2cpp
	@if [ ! -d "$(EXAMPLES_DIR)" ]; then \
		mkdir -p $(EXAMPLES_DIR); \
	fi
	@for bf_file in $(EXAMPLES_DIR)/*.bf; do \
		if [ -f "$$bf_file" ]; then \
			cpp_file="$${bf_file%.bf}.cpp"; \
			./$(TRANSLATOR) "$$bf_file" "$$cpp_file"; \
		fi; \
	done

# Compile all .cpp files in examples directory
examples: convert
	@for cpp_file in $(EXAMPLES_DIR)/*.cpp; do \
		if [ -f "$$cpp_file" ]; then \
			exe_name="$${cpp_file%.cpp}"; \
			echo "Compiling $$cpp_file -> $$exe_name"; \
			$(CXX) $(CXXFLAGS) -I. "$$cpp_file" $(SOURCES) -o "$$exe_name" || echo "  Failed to compile $$cpp_file"; \
		fi; \
	done

# Clean all binaries and .o files
clean:
	rm -f $(TRANSLATOR)
	@find $(EXAMPLES_DIR) -type f ! -name "*.bf" -delete 2>/dev/null || true

# Show help message
help:
	@echo "Available targets:"
	@echo "  all        - Compile bf2cpp, convert all .bf files, and compile examples"
	@echo "  bf2cpp     - Compile the bf2cpp tool"
	@echo "  convert    - Convert all .bf files in examples/ to .cpp files"
	@echo "  examples   - Compile all .cpp files in examples/ to executables"
	@echo "  clean      - Remove all binaries and .o files"
	@echo "  help       - Show this help message"

.PHONY: all bf2cpp convert examples clean help
