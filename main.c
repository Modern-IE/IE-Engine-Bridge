#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

const char* htaContent = 
"<!DOCTYPE html><html><head><title>RetroBrowse</title>"
"<hta:application id='oApp' border='thick' caption='yes' showintaskbar='yes' windowstate='normal'>"
"<style>body{margin:0;overflow:hidden;}.bar{padding:5px;background:#eee;border-bottom:1px solid #ccc;}"
"input{width:80%;}iframe{width:100%;height:90vh;border:none;}</style>"
"<script>function nav(){var u=document.getElementById('u').value;if(!u.startsWith('http'))u='http://'+u;document.getElementById('f').src=u;}</script>"
"</head><body><div class='bar'><input type='text' id='u' value='www.bing.com'><button onclick='nav()'>GO</button></div>"
"<iframe id='f' src='https://www.bing.com' application='yes'></iframe></body></html>";

int main() {
    char tempPath[MAX_PATH];
    char htaFilePath[MAX_PATH];
    DWORD pathLen = GetTempPath(MAX_PATH, tempPath);
    if (pathLen == 0) {
        return 1;
    }
    snprintf(htaFilePath, MAX_PATH, "%sRetroBrowse.hta", tempPath);
    FILE *file = fopen(htaFilePath, "w");
    if (file == NULL) {
        return 1;
    }
    fprintf(file, "%s", htaContent);
    fclose(file);
    HINSTANCE result = ShellExecute(NULL, "open", htaFilePath, NULL, NULL, SW_SHOWNORMAL);

    if ((INT_PTR)result <= 32) {
        printf("ERROR: %ld\n", (long)result);
        return 1;
    }

    Sleep(2000);

    return 0;
}
