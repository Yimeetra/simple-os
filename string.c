int strlen(char *string) {
    int i = 0;
    for (; string[i] != 0; ++i);
    return i;
}