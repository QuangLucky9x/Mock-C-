# Định nghĩa biến
CXX = g++
CXXFLAGS = -Wall -Wextra -g
LDFLAGS = `pkg-config --cflags --libs taglib` `sdl2-config --cflags --libs` -lSDL2 -lSDL2_mixer

# Thư mục chứa các tệp nguồn
SRCDIR = src
# Thư mục chứa các tệp tiêu đề
HDRDIR = include
# Thư mục chứa các tệp đầu ra (đối tượng và chương trình)
BUILDDIR = build

# Tệp nguồn
SRCS = $(wildcard $(SRCDIR)/*.cpp)
# Tệp tiêu đề
HDRS = $(wildcard $(HDRDIR)/*.h)

# Tên chương trình đầu ra
TARGET = main

# Tạo các đường dẫn tệp đối tượng tương ứng
OBJS = $(SRCS:$(SRCDIR)/%.cpp=$(BUILDDIR)/%.o)

# Phần quy tắc biên dịch các tệp .cpp thành các tệp .o
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp $(HDRS)
	$(CXX) $(CXXFLAGS) -c $< -o $@ -I./$(HDRDIR)

# Phần quy tắc liên kết các tệp đối tượng .o với .dll thành chương trình thực thi .exe
$(TARGET): $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS)

# Quy tắc mặc định sẽ chạy mục tiêu cuối cùng
.DEFAULT_GOAL := $(TARGET)

# Xóa các tệp đối tượng và các tệp đầu ra khi thực hiện "make clean"
clean:
	rm -rf $(BUILDDIR)/*.o $(TARGET)