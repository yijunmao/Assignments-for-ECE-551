#include <ctype.h>
#include <grp.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

//This function is for Step 4
char * time2str(const time_t * when, long ns) {
  char * ans = malloc(128 * sizeof(*ans));
  char temp1[64];
  char temp2[32];
  const struct tm * t = localtime(when);
  strftime(temp1, 512, "%Y-%m-%d %H:%M:%S", t);
  strftime(temp2, 32, "%z", t);
  snprintf(ans, 128, "%s.%09ld %s", temp1, ns, temp2);
  return ans;
}

//print the first three lines
void printFirstThreeLines(const char * filename, struct stat * sb) {
  //declare variables for file size, number of blocks, block size, and file type
  off_t total_size = sb->st_size;
  blkcnt_t num_blcoks = sb->st_blocks;
  blksize_t block_size = sb->st_blksize;
  char * file_type;

  //determine file type
  switch (sb->st_mode & S_IFMT) {
    case S_IFBLK:
      file_type = "block special file";
      break;
    case S_IFCHR:
      file_type = "character special file";
      break;
    case S_IFDIR:
      file_type = "directory";
      break;
    case S_IFIFO:
      file_type = "fifo";
      break;
    case S_IFLNK:
      file_type = "symbolic link";
      break;
    case S_IFREG:
      if (total_size != 0) {
        file_type = "regular file";
      }
      // corner case when file is empty
      else {
        file_type = "regular empty file";
      }
      break;
    case S_IFSOCK:
      file_type = "socket";
      break;
    default:
      file_type = "unknown?";
      break;
  }

  // declare varialbes for device_id, inode number and hardlink_number
  dev_t device_id = sb->st_dev;
  ino_t inode_number = sb->st_ino;
  nlink_t hardlink_number = sb->st_nlink;

  // corner case when filename is a link
  if ((sb->st_mode & S_IFMT) == S_IFLNK) {
    char linktarget[256];
    /*if (strlen(filename) > 255) {
      fprintf(stderr, "Too long symbolic pathname!\n");
      exit(EXIT_FAILURE);
    }*/

    ssize_t num_chars = readlink(filename, linktarget, 256);
    linktarget[num_chars] = '\0';

    printf("  File: %s -> %s\n", filename, linktarget);
  }

  else {
    printf("  File: %s\n", filename);
  }

  printf("  Size: %-10lu\tBlocks: %-10lu IO Block: %-6lu %s\n",
         total_size,
         num_blcoks,
         block_size,
         file_type);

  // character special file or block special file! use st_rdev instead of st_dev
  if ((sb->st_mode & S_IFMT) == S_IFCHR || (sb->st_mode & S_IFMT) == S_IFBLK) {
    int major_id = major(sb->st_rdev);
    int minor_id = minor(sb->st_rdev);
    printf("Device: %lxh/%lud\tInode: %-10lu  Links: %-5lu Device type: %d,%d\n",
           device_id,
           device_id,
           inode_number,
           hardlink_number,
           major_id,
           minor_id);
  }

  // print for normal files
  else {
    printf("Device: %lxh/%lud\tInode: %-10lu  Links: %lu\n",
           device_id,
           device_id,
           inode_number,
           hardlink_number);
  }
}

// print the fourth line
void printFourthLine(struct stat * sb) {
  // print first part of fourth line: to the end of access
  // permissions in octal
  mode_t permission_octal = (sb->st_mode & ~S_IFMT);

  // human readable description of the permissions, 10 characters in total
  // first character depends on file type
  char first = ' ';
  switch (sb->st_mode & S_IFMT) {
    case S_IFBLK:
      first = 'b';
      break;
    case S_IFCHR:
      first = 'c';
      break;
    case S_IFDIR:
      first = 'd';
      break;
    case S_IFIFO:
      first = 'p';
      break;
    case S_IFLNK:
      first = 'l';
      break;
    case S_IFREG:
      first = '-';
      break;
    case S_IFSOCK:
      first = 's';
      break;
    default:
      printf("unknown?\n");
      break;
  }

  // second character depends on if the file is readable by the owner
  char second;
  if ((sb->st_mode & S_IRUSR) != 0) {
    second = 'r';
  }
  else {
    second = '-';
  }

  // third character depends on if the file is writable by the owner
  char third;
  if ((sb->st_mode & S_IWUSR) != 0) {
    third = 'w';
  }
  else {
    third = '-';
  }

  // fourth character depends on if the file is executable by the owner
  char fourth;
  if ((sb->st_mode & S_IXUSR) != 0) {
    fourth = 'x';
  }
  else {
    fourth = '-';
  }

  // characters five to seven similar to the previous three, but for the group rather than the owner
  char fifth;
  if ((sb->st_mode & S_IRGRP) != 0) {
    fifth = 'r';
  }
  else {
    fifth = '-';
  }

  char sixth;
  if ((sb->st_mode & S_IWGRP) != 0) {
    sixth = 'w';
  }
  else {
    sixth = '-';
  }

  char seventh;
  if ((sb->st_mode & S_IXGRP) != 0) {
    seventh = 'x';
  }
  else {
    seventh = '-';
  }

  // characters eight to ten similar to the previous three, but for other
  char eighth;
  if ((sb->st_mode & S_IROTH) != 0) {
    eighth = 'r';
  }
  else {
    eighth = '-';
  }

  char ninth;
  if ((sb->st_mode & S_IWOTH) != 0) {
    ninth = 'w';
  }
  else {
    ninth = '-';
  }

  char tenth;
  if ((sb->st_mode & S_IXOTH) != 0) {
    tenth = 'x';
  }
  else {
    tenth = '-';
  }

  char human_read_permission[] = {
      first, second, third, fourth, fifth, sixth, seventh, eighth, ninth, tenth, '\0'};

  // print second part of fourth line: starting from userid
  uid_t user_id = sb->st_uid;

  struct passwd * password = getpwuid(user_id);

  char * user_name = password->pw_name;

  gid_t group_id = sb->st_gid;

  struct group * group_info = getgrgid(group_id);

  char * group_name = group_info->gr_name;

  printf("Access: (%04o/%s)  Uid: (%5d/%8s)   Gid: (%5d/%8s)\n",
         permission_octal,
         human_read_permission,
         user_id,
         user_name,
         group_id,
         group_name);
}

// print the last four lines
void printLastFourLines(struct stat * sb) {
  // get access/modify/change time transformed to a string
  char * access_time = time2str(&(sb->st_atime), sb->st_atim.tv_nsec);
  char * modify_time = time2str(&(sb->st_mtime), sb->st_mtim.tv_nsec);
  char * change_time = time2str(&(sb->st_ctime), sb->st_ctim.tv_nsec);

  //print the result
  printf("Access: %s\nModify: %s\nChange: %s\n Birth: -\n", access_time, modify_time, change_time);

  //free the allocated memory
  free(access_time);
  free(modify_time);
  free(change_time);
}

int main(int argc, char * argv[]) {
  // check number of arguments
  if (argc < 2) {
    fprintf(stderr, "Usage: %s <pathname>\n", argv[0]);
    return EXIT_FAILURE;
  }

  /*
  struct stat sb;

  if (lstat(argv[1], &sb) == -1) {
    perror("lstat");
    exit(EXIT_FAILURE);
  }

  printFirstThreeLines(argv[1], &sb);

  printFourthLine(&sb);

  printLastFourLines(&sb);
  */

  // loop to print information of all the files
  for (int i = 1; i < argc; i++) {
    struct stat sb;

    if (lstat(argv[i], &sb) == -1) {
      // corner cases when filename is too long or file does not exist in the current directory
      fprintf(stderr, "stat: cannot stat '%s': ", argv[i]);
      perror("");
      exit(EXIT_FAILURE);
    }

    printFirstThreeLines(argv[i], &sb);

    printFourthLine(&sb);

    printLastFourLines(&sb);
  }

  return EXIT_SUCCESS;
}
