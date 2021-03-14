#include<stdint.h>
#include<string.h>
#define int int32_t
char *mystrchr (const char *s, int c){
	do {
		if (*s == c) return (char*)s;
	} while (*s++);
	return (0);
}
char *mystrrchr (const char *s, int c){
	const char *fd, *p;
	c = (unsigned char) c;
	if (c == '\0') return strchr (s, '\0');
	fd = NULL;
	while ((p = strchr (s, c)) != NULL){
    	fd = p;
    	s = p + 1;
    }
	return (char *)fd;
}
size_t mystrspn(const char *s,const char *accept){
    const char *p, *a;
    int cnt = 0;
    for(p = s; *p != '\0'; p++){
        for (a = accept; *a != '\0'; ++a) if (*p == *a) break;
        if (*a == '\0') return (size_t)cnt;
        cnt++;
    }
    return (size_t)cnt;
}
size_t mystrcspn(const char *s, const char *reject){
    int len =0;
    if((s == NULL) || (reject == NULL)) return len;
    while(*s){
        if(strchr(reject,*s)) return (size_t)len;
        else{
            s++;
            len++;
        }
    }
    return (size_t)len;
}
char *mystrpbrk(const char *s, const char *accept){
    if((s == NULL) || (accept == NULL)) return NULL;
    while(*s){
        if(strchr(accept, *s)) return (char *)s;
        else s++;
    }
    return NULL;
}
const char* mystrstr(const char *haystack, const char *needle){
    if (*needle == '\0') return (char *)haystack;
    for (int i = 0; i < (int)strlen(haystack); i++){
        if (*(haystack + i) == *needle){
            char *ptr = strstr(haystack + i + 1, needle + 1);
            return (ptr) ? ptr - 1 : NULL;
        }
    }
    return NULL;
}
char *mystrtok(char * str, const char * delim){
    static char *p = 0;
    if(str) p = str;
    else if(!p) return 0;
    str = p + strspn(p, delim);
    p = str + strcspn(str, delim);
    if(p == str) return p = 0;
    p = *p ? *p = 0,p + 1 : 0;
    return (char *)str;
}