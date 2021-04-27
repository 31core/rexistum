struct file
{
	int inode;
	int seek;
};

int file_create(struct file*, char*); //创建文件
int file_open(struct file *file, char*); //打开文件
void file_write(struct file*, char*, int); //写入文件
int file_read(struct file*, char*, int); //读取文件
void file_remove(char*); //删除文件
void file_get_name_by_inode(char*, int); //通过inode获取文件名