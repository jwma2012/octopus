#ifndef LEAFFS_COMMON_LEASE_H_
#define LEAFFS_COMMON_LEASE_H_

#include "common.hpp"

namespace leaffs {

namespace {
enum LeaseState {
    kFree,
    kRead,
    kWrite,
};

enum MetadataType {
    kDir,
    kFile,
};

static const uint64_t kEpsilon = 10 * 1000;
static const uint64_t kLeaseTime = 1000 * 1000; //1秒钟

} //anonymous namespace

class LeaseEntry() {
public:
    LeaseEntry() { }
    virtual ~LeaseEntry() {printf("lease\n")};

    static uint64_t GetLeaseDue() {
        return lease_due_;
    }

    static void SetMetadataType(MetadataType e) {
        metadata_type_ = e;
    }

private:
    int16_t src_server_;
    int lease_state_;
    uint64_t lease_due_;
    int metadata_type_;

    LookupCache* cache_;
    Cache::Handle* handle_;
    friend class LookupCache;

    // No copying allowed
    LeaseEntry(const LeaseEntry&);
    LeaseEntry& LeaseEntry=(const LeaseEntry&);
}

class DirMetaEntry : public LeaseEntry{
public:
    DirMetaEntry(DirectoryMeta* m) {
        ptr_dir_meta_ = new DirectoryMeta();
        memcpy(ptr_dir_meta_, m, sizeof(DirectoryMeta)); //深拷贝
        LeaseEntry::SetMetadataType(kDir);
    }
    virtual ~DirMetaEntry() { {printf("DirMetaEntry\n")}; delete ptr_dir_meta_}
    DirectoryMeta *GetDirMeta() {
        return ptr_dir_meta_;
    }

private:
    DirectoryMeta* ptr_dir_meta_;

    // No copying allowed
    DirMetaEntry(const DirMetaEntry&);
    DirMetaEntry& operator=(const DirMetaEntry&);
};

class FileMetaEntry : public LeaseEntry{
public:
    FileMetaEntry() {
        ptr_file_meta_ = new FileMeta();
        memcpy(ptr_file_meta_, m, sizeof(FileMeta)); //深拷贝
        LeaseEntry::SetMetadataType(kFile);
    }
    virtual ~FileMetaEntry() { {printf("FileMetaEntry\n")}; delete ptr_file_meta_}
    FileMeta *GetFileMeta() {
        return ptr_file_meta_;
    }

private:
    FileMeta* ptr_file_meta_;

    // No copying allowed
    FileMetaEntry(const FileMetaEntry&);
    FileMetaEntry& operator=(const FileMetaEntry&);
};


} /* namespace leaffs*/
#endif /* LEAFFS_COMMON_LEASE_H_ */