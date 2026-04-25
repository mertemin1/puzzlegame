# --- DERLEYİCİ VE STANDART AYARLARI ---
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I. -MMD -MP

# --- DOSYALAR ---
# Derlenecek bütün .cpp dosyalarımız (textures.cpp çıkarıldı)
SRCS = main.cpp grid.cpp sprite.cpp
OBJS = $(SRCS:.cpp=.o)
DEPS = $(OBJS:.o=.d)

# --- İŞLETİM SİSTEMİNE GÖRE SFML YOLLARI OTOMATİK SEÇİMİ ---
ifeq ($(OS),Windows_NT)
    # WINDOWS AYARLARI
    TARGET = Sokoban.exe
    SFML_DIR = SFML/windows
    # Include ve Lib yolları
    CXXFLAGS += -I$(SFML_DIR)/include -DSFML_STATIC
    LDFLAGS = -static -static-libgcc -static-libstdc++ -L$(SFML_DIR)/lib -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lgdi32 -lwinmm -lfreetype -luser32 -lkernel32 -lshell32
    
    # Temizleme komutu (Windows cmd için - .d dosyaları eklendi)
    CLEAN_CMD = del /Q *.o *.d $(TARGET)
else
    # LINUX AYARLARI
    TARGET = Sokoban
    SFML_DIR = SFML/linux
    
    # Include ve Lib yolları
    CXXFLAGS += -I$(SFML_DIR)/include
    
    # Linux'ta dinamik kütüphaneleri (.so) bulabilmesi için rpath ekliyoruz
    LDFLAGS = -L$(SFML_DIR)/lib -Wl,-rpath=$(SFML_DIR)/lib -lsfml-graphics -lsfml-window -lsfml-system
    
    # Temizleme komutu (Linux bash için - .d dosyaları eklendi)
    CLEAN_CMD = rm -f *.o *.d $(TARGET)
endif

# --- DERLEME KURALLARI ---

# Varsayılan kural (Sadece 'make' yazınca çalışır)
all: $(TARGET)

# Ana programı bağlama (Linking)
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS)

# .cpp dosyalarını .o (object) ve .d dosyalarına çevirme
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 'make clean' yazınca ortalığı temizler
clean:
	$(CLEAN_CMD)
	@echo "Temizlik tamamlandi!"

-include $(DEPS)