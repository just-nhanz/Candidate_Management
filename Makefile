# ─── Compiler & flags ─────────────────────────────────────────────────────────
CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -I include

# ─── Targets ──────────────────────────────────────────────────────────────────
TARGET    = candidate_manager
BENCHMARK = tests/benchmark
SRCDIR    = src
OBJDIR    = obj

# ─── Source lists ─────────────────────────────────────────────────────────────
MAIN_SRC = main.cpp \
           $(SRCDIR)/Candidate.cpp \
           $(SRCDIR)/Node.cpp \
           $(SRCDIR)/LinkedList.cpp \
           $(SRCDIR)/HashTable.cpp \
           $(SRCDIR)/CandidateSorter.cpp \
           $(SRCDIR)/GroupManager.cpp \
           $(SRCDIR)/RoomManager.cpp \
           $(SRCDIR)/FileManager.cpp \
           $(SRCDIR)/CandidateManager.cpp

BENCH_SRC = tests/benchmark.cpp \
            $(SRCDIR)/Candidate.cpp \
            $(SRCDIR)/Node.cpp \
            $(SRCDIR)/LinkedList.cpp \
            $(SRCDIR)/HashTable.cpp \
            $(SRCDIR)/CandidateSorter.cpp \
            $(SRCDIR)/FileManager.cpp

MAIN_OBJ  = $(patsubst %.cpp, $(OBJDIR)/%.o,       $(notdir $(MAIN_SRC)))
BENCH_OBJ = $(patsubst %.cpp, $(OBJDIR)/bench_%.o, $(notdir $(BENCH_SRC)))

.PHONY: all run benchmark clean help

# ─── Default target ───────────────────────────────────────────────────────────
all: $(OBJDIR) $(TARGET)
	@echo ""
	@echo "  ✓ Build thanh cong → ./$(TARGET)"
	@echo "  Chay: make run"

$(TARGET): $(MAIN_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

# ─── Benchmark ────────────────────────────────────────────────────────────────
benchmark: $(OBJDIR) $(BENCHMARK)
	@echo "  ✓ Benchmark → ./$(BENCHMARK)"

$(BENCHMARK): $(BENCH_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

# ─── Object rules ─────────────────────────────────────────────────────────────
$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(OBJDIR)/main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/bench_benchmark.o: tests/benchmark.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/bench_%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# ─── Run / Clean / Help ───────────────────────────────────────────────────────
run: all
	./$(TARGET)

clean:
	rm -rf $(OBJDIR) $(TARGET) $(BENCHMARK)
	@echo "  ✓ Da xoa cac file build."

help:
	@echo ""
	@echo "  HUONG DAN BUILD"
	@echo "  ─────────────────────────────────────────"
	@echo "  make            Build chuong trinh chinh"
	@echo "  make run        Build va chay chuong trinh"
	@echo "  make benchmark  Build tool do hieu nang"
	@echo "  make clean      Xoa tat ca file build"
	@echo "  make help       Hien thi huong dan nay"
	@echo ""
