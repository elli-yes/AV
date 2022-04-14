#include "headers.hpp"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <zip.h>

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

using namespace std;
int enumerateArchive(char *filePath, const char *archiveRoot);

static int writeCurrentFile(int i, struct zip *za, struct zip_stat zipStat, char bufForFileName[])
{

  struct zip_file *zipFile;  // Структура для работы с текущим файлом архива
  int fd;                    // Файловый дескриптор
  zip_int64_t lenOfReadData; // Сколько байт было прочитано из файла
  char buf[512];             // Буфер для чтения информации из архива
  char pswd[255];            // Password for archive

  if (zipStat.encryption_method)
  {
    cout << "Pass for " << zipStat.name << "\n";
    cin >> pswd;
    zipFile = zip_fopen_index_encrypted(za, i, 0, pswd);
  }
  else
  {
    zipFile = zip_fopen_index(za, i, 0);
  }
  if (!zipFile)
  {

    return 1;
  }
  fd = open(bufForFileName, O_RDWR | O_TRUNC | O_CREAT, 0644); //Создать файл
  if (fd < 0)
  { // Если файл нельзя создать, значит произошла ошибка

    zip_fclose(zipFile);
    return 1;
  }
  zip_uint64_t sum = 0; // Полный размер текущего файла в архиве
  while (sum != zipStat.size)
  {

    lenOfReadData = zip_fread(zipFile, buf, sizeof(buf) * sizeof(buf[0]));
    if (lenOfReadData < 0)
    {

      zip_fclose(zipFile);
      return 1;
    }
    write(fd, buf, lenOfReadData);
    sum += lenOfReadData;
  }
  close(fd);
  int zipCloseResult = zip_fclose(zipFile);
  if (zipCloseResult != 0)
  {

    return 1;
  }
  return 0;
}
static int loopThroughFiles(const char *archiveRoot, struct zip *za, const char *filePath)
{

  int i;                        // Переменная для итерирования
  struct zip_stat zipStat;      // Информация о файле
  size_t currentItemNameLength; // Длина имени текущего элемента в архиве

  for (i = 0; i < zip_get_num_entries(za, 0); i++)
  {

    if (zip_stat_index(za, i, 0, &zipStat) == 0)
    {

      currentItemNameLength = strlen(zipStat.name);
      // cout << "Имя файла: [ " << zipStat.name <<
      // printf("Размер: [%llu], ", zipStat.size);
      // printf("Зашифрован: [%llu], ", zipStat.encryption_method);
      // printf("\n");
      char bufForFileName[300]; // Буфер для имени файла с учётом корневой папки
      strcpy(bufForFileName, archiveRoot);
      strcat(bufForFileName, zipStat.name);
      if (zipStat.name[currentItemNameLength - 1] == '/')
      { // Если текущий элемент архива - папка, то нужно создать папку на диске

        if (mkdir(bufForFileName, S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH) < 0)
        { // Если не удалось создать папку
          if (errno != EEXIST)
          { // Если не удалось создать папку по причине того, что она уже была создана, то всё нормально, иначе завершим программу

            return 1;
          }
        }
      }
      else if (string(zipStat.name).find(".zip") != -1)
      {
        writeCurrentFile(i, za, zipStat, bufForFileName);
        char zipper[255] = "/home/egor/AV/zip/";
        strcat(zipper, zipStat.name);
        // cout << zipper << "   ZIPPER\n";1

        enumerateArchive(zipper, archiveRoot);
        remove(zipper);
      }
      else
      { // Текущий элемент - файл, а значит нужно последовательно считать все данные и записать их на диск

        writeCurrentFile(i, za, zipStat, bufForFileName);
      }
    }
  }
  return 0;
}
int enumerateArchive(char *filePath, const char *archiveRoot)
{

  struct zip *za; // Структура для работы с архивом
  int err;        // Код последней ошибки
  // Попытаться открыть файл с архивом, если не получилось - сообщить об ощибке
  if ((za = zip_open(filePath, ZIP_RDONLY, &err)) == NULL)
  {

    return 1;
  }
  // Пройтись по всем элементам архива
  loopThroughFiles(archiveRoot, za, filePath);
  // Закрыть файл с архивом (если не получилось - сообщить об ошибке)
  if (zip_close(za) == -1)
  {

    return 1;
  }
  return 0;
}

int AVZip(char *path)
{
  cout << path << "\n";
  enumerateArchive(path, "/home/egor/AV/zip/");

  return 0;
}