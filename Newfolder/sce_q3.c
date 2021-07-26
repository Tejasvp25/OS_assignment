int main()
{
    int fd[2];
    pipe(fd);
    int rc = fork();
    if (rc == 0)
    { //child
        close(fd[1]);
        printf("child1\n");
        // read(fd[0], bufc, bufc_size);
        printf("child2\n");
    }
    else
    { //parent
        close(fd[0]);
        printf("parent1\n");
        // write(fd[1], bufp, bufp_size);
        wait();
        printf("parent2\n");
    }
    return 0;
}