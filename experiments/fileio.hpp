#pragma once

#include <cstdlib>
#include <sys/mman.h>
#include <fcntl.h>

namespace fileio {

constexpr size_t SegSize = 4096;

enum class Access {
    READ,
    WRITE,
};

class File {
public:
    File() = delete;
    File(const char* filename, off_t segOffset);
    // File(const char* filename, size_t size);
    ~File();
    unsigned char operator[] (const size_t idx);
    size_t getFileSize() const;
    size_t getSegSize() const;
    size_t copySegment(size_t size, off_t offset, void* ptr) const;
    // size_t editSegment(size_t size, off_t offset, void* ptr);
    void* getSegment() const;
    void* nextSegment();
    void* prevSegment();
private:
    int m_fd{0};
    size_t m_fileSize{0};
    size_t m_segSize{0};
    off_t m_segOffset{0};
    void* m_buf{nullptr};
    int m_fileFlags{O_RDONLY};
    int m_mmapFlags{PROT_READ};
};

} // namespace fileio