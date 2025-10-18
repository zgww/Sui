#pragma once
/* MD5.H - header file for MD5.C
 */
 
/* Copyright (C) 1991-2, RSA Data Security, Inc. Created 1991. All
rights reserved.
 
License to copy and use this software is granted provided that it
is identified as the "RSA Data Security, Inc. MD5 Message-Digest
Algorithm" in all material mentioning or referencing this software
or this function.
 
License is also granted to make and use derivative works provided
that such works are identified as "derived from the RSA Data
Security, Inc. MD5 Message-Digest Algorithm" in all material
mentioning or referencing the derived work.
 
RSA Data Security, Inc. makes no representations concerning either
the merchantability of this software or the suitability of this
software for any particular purpose. It is provided "as is"
without express or implied warranty of any kind.
 
These notices must be retained in any copies of any part of this
documentation and/or software.
 */
 
 #define MD5_VALUE_LEN      16      //MD5数值的长度
 #define MD5_STRING_LEN     (32+1)  //MD5字符串的长度
 
typedef unsigned char MD5[MD5_VALUE_LEN];   //MD5的数值类型
typedef char MD5_STR[MD5_STRING_LEN];       //MD5的字符串类型
 
/*  计算文件的MD5值
* INPUT:
*   filename:	要计算的文件
*   digest:		用于存储计算结果
* RETURN:
*   0:	正常结束
*   -1:	无法打开文件
*/
int MD5File(const char *filename, MD5 digest);
 
/*  计算内存块的MD5值
* INPUT:
*   buffer:	内存块的起始地址
*   size:	内存块的长度
*   digest:	用于存储计算结果
*/
void MD5Buffer(void *buffer, size_t size, MD5 digest);
 
/*  测试MD5程序正确性
* RETURN:
*   0:	MD5正常运行
*   -1:	MD5无法正常运行
*/
int MD5Test(void);
 
/*  将MD5值打印到屏幕
* INPUT:
*   digest:	要打印的MD5值
*/
void MD5Print(MD5 digest);
 
/*  将MD5值转换为MD5字符串
* INPUT:
*   digest:	用于转换的MD5值
*   str:	用于存放转换结果
*/
void MD5String(MD5 digest, MD5_STR str);
 