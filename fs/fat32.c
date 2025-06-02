#include "fs/fat32.h"
// #include "fs/mbr.h"
#include "fs/virtio.h"
// #include "memory.h"
#include "printk.h"
// #include "string.h"
#include <stdint.h>

struct fat32_bpb fat32_header;
struct fat32_volume fat32_volume;

uint8_t fat32_buf[VIRTIO_BLK_SECTOR_SIZE];
uint8_t fat32_table_buf[VIRTIO_BLK_SECTOR_SIZE];

uint64_t cluster_to_sector(uint64_t cluster) {
    return (cluster - 2) * fat32_volume.sec_per_cluster +
           fat32_volume.first_data_sec;
}

uint32_t next_cluster(uint64_t cluster) {
    uint64_t fat_offset = cluster * 4;
    uint64_t fat_sector =
        fat32_volume.first_fat_sec + fat_offset / VIRTIO_BLK_SECTOR_SIZE;
    virtio_blk_read_sector(fat_sector, fat32_table_buf);
    int index_in_sector =
        fat_offset % (VIRTIO_BLK_SECTOR_SIZE / sizeof(uint32_t));
    return *(uint32_t *)(fat32_table_buf + index_in_sector);
}

void fat32_test(uint64_t fat_start) {
    virtio_blk_read_sector(fat_start, fat32_buf);
    uint32_t *buf = (uint32_t *)fat32_buf;
    if (buf[0] == 0x0ffffff8) {
        printk("[DEBUG] get the right start of fat\n");
    } else {
        printk("[ERROR] get the wrong start of fat\n");
    }
}

void fat32_init(uint64_t lba, uint64_t size) {
    virtio_blk_read_sector(lba, (void *)&fat32_header);
    fat32_volume.first_fat_sec = fat32_header.rsvd_sec_cnt + lba;
    printk("[DEBUG] start of fat sector is 0x%x\n", fat32_volume.first_fat_sec);
    fat32_volume.sec_per_cluster = 1;
    fat32_volume.first_data_sec =
        fat32_header.rsvd_sec_cnt +
        (fat32_header.num_fats * fat32_header.fat_sz32) + lba;
    printk("[DEBUG] start of data sector is 0x%x\n",
           fat32_volume.first_data_sec);
    fat32_volume.fat_sz = fat32_header.fat_sz32;
    fat32_test(fat32_volume.first_fat_sec);
}

int is_fat32(uint64_t lba) {
    virtio_blk_read_sector(lba, (void *)&fat32_header);
    if (fat32_header.boot_sector_signature != 0xaa55) {
        return 0;
    }
    return 1;
}

int next_slash(const char *path) {
    int i = 0;
    while (path[i] != '\0' && path[i] != '/') {
        i++;
    }
    if (path[i] == '\0') {
        return -1;
    }
    return i;
}

void to_upper_case(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= 'a' && str[i] <= 'z') {
            str[i] -= 32;
        }
    }
}

struct fat32_file fat32_open_file(const char *path) {
    struct fat32_file file;
    /* TODO */
    return file;
}

int64_t fat32_lseek(struct file *file, int64_t offset, uint64_t whence) {
    if (whence == SEEK_SET) {
        file->cfo = 0;
    } else if (whence == SEEK_CUR) {
        file->cfo = 0;
    } else if (whence == SEEK_END) {
        file->cfo = 0;
    } else {
        printk("fat32_lseek: whence not implemented\n");
        while (1)
            ;
    }
    return file->cfo;
}

uint64_t fat32_table_sector_of_cluster(uint32_t cluster) {
    return fat32_volume.first_fat_sec +
           cluster / (VIRTIO_BLK_SECTOR_SIZE / sizeof(uint32_t));
}

int64_t fat32_read(struct file *file, void *buf, uint64_t len) {
    /* TODO */
    return 0;
}

int64_t fat32_write(struct file *file, const void *buf, uint64_t len) {
    /* TODO */
    return 0;
}
