# Компилятор и флаги
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g -Iinclude

# Пути
SRCDIR = src
INCDIR = include
BUILDDIR = build

# Исходники и объекты
SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(SOURCES:$(SRCDIR)/%.c=$(BUILDDIR)/%.o)
TARGET = $(BUILDDIR)/student_manager

# Цель по умолчанию
all: $(TARGET)

# Создание папки build
$(BUILDDIR):
	mkdir -p $@

# Сборка объектных файлов
$(BUILDDIR)/%.o: $(SRCDIR)/%.c $(INCDIR)/header.h | $(BUILDDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Сборка исполняемого файла
$(TARGET): $(OBJECTS) | $(BUILDDIR)
	$(CC) $^ -o $@

# Очистка
clean:
	rm -rf $(BUILDDIR)

# Пересборка
rebuild: clean all

.PHONY: all clean rebuild