#include <fcntl.h>
#include <sys/mman.h>
#include <cerrno>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <sys/stat.h>
#include "fileio.hpp"
#include <unistd.h>
#include <cassert>
#include <cstring>
#include <type_traits>

namespace fileio {

static_assert(SegSize % 4096 == 0);

File::File(const char* filename, off_t segOffset) {  
   
    /*
    } else if (prot == Access::WRITE) {
        file_flags = O_CREAT|O_WRONLY|O_TRUNC;
        mmap_flags = PROT_WRITE;
    }
    */

    m_fd = open(filename, m_fileFlags);
    if (m_fd < 0) {
        perror("open file error");
        exit(errno);
    }
    // lseek(fd, offset, SEEK_SET) == -1

    struct stat statbuf;
    if (fstat(m_fd, &statbuf) < 0) {
        perror("fstat error");
        exit(errno);
    }

    m_segOffset = segOffset * SegSize;
    m_fileSize = statbuf.st_size;

    if (m_segOffset >= m_fileSize) {
        perror("segOffset out of range");
        exit(-1);
    }

    m_segSize = (m_segOffset + SegSize <= m_fileSize)? SegSize : m_fileSize - m_segOffset;

    
    
    m_buf = mmap(NULL, m_segSize, m_mmapFlags, MAP_SHARED, m_fd, m_segOffset);
    if (m_buf == MAP_FAILED) {
        perror("map failure");
        exit(errno);
    }
}

File::~File() {
    if (munmap(m_buf, m_segSize) == -1) {
        perror("munmap error");
        exit(errno);
    }
    if (close(m_fd) == -1) {
        perror("close file error");
        exit(errno);
    }
}

void* File::nextSegment() {
    // correct
    if (m_segOffset + SegSize >= m_fileSize) {
        return nullptr;
    }
    
    if (munmap(m_buf, m_segSize) == -1) {
        perror("munmap error");
        exit(errno);
    }

    m_segOffset += SegSize;
    m_segSize = (m_segOffset + SegSize <= m_fileSize)? SegSize : m_fileSize - m_segOffset;


    m_buf = mmap(NULL, m_segSize, m_mmapFlags, MAP_SHARED, m_fd, m_segOffset);
    if (m_buf == MAP_FAILED) {
        perror("map failure");
        exit(errno);
    }
    return m_buf;
}

void* File::prevSegment() {
    // correct
    if (m_segOffset - SegSize < 0) {
        return nullptr;
    }
    
    if (munmap(m_buf, m_segSize) == -1) {
        perror("munmap error");
        exit(errno);
    }

    m_segOffset -= SegSize;
    m_segSize = SegSize;

    m_buf = mmap(NULL, m_segSize, m_mmapFlags, MAP_SHARED, m_fd, m_segOffset);
    if (m_buf == MAP_FAILED) {
        perror("map failure");
        exit(errno);
    }
    return m_buf;
}

void* File::getSegment() const {
    assert(m_buf != nullptr);
    return m_buf;
}

size_t File::getFileSize() const {
    return m_fileSize;
}

size_t File::getSegSize() const {
    return m_segSize;
}
unsigned char File::operator[] (const size_t idx) {
    assert(idx < SegSize);
    unsigned char* ptr = (unsigned char*)((uint64_t)m_buf + idx);
    return *ptr;
}

size_t File::copySegment(size_t size, off_t offset, void* ptr) const {
    if (size > m_segSize - offset) {
        ptr = nullptr;
        return 0;
    }
    
    void* src = (void*)((uint64_t)m_buf + offset);
    ptr = memcpy(ptr, src, size);
    assert(ptr != nullptr);
    return size;
}



} // namespace fileio