#include "../includes/game.h"


void wait_for_child(pid_t pid)
{
    // int status;
    // waitpid(pid, &status, 0);
}

void play_sound(t_sound *sound)
{
    if (sound->is_playing)
    {
        kill(sound->pid, SIGTERM);
        wait_for_child(sound->pid);
        sound->is_playing = 0;
    }
    pid_t pid = fork();
    if (pid == 0)
    {
        execlp("aplay", "aplay", sound->file_path, NULL);
        exit(0);
    }
    else if (pid > 0)
    {
        sound->pid = pid;
        sound->is_playing = 1;
    }
    else 
        write(2, "Error: fork failed\n", 19);
}

void stop_sound(t_sound *sound)
{
    if (sound->is_playing)
    {
        kill(sound->pid, SIGTERM);
        wait_for_child(sound->pid);
        sound->is_playing = 0;
    }
}

void stop_all_sounds(t_data *data)
{
    // int i = 0;
    // while (i < 5)
    //     stop_sound(&data->sounds[i++]);
}