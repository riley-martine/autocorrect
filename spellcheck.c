#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <argp.h>
#include <regex.h>
#include "llist_queue.h"
#include "dictfreq.h"

Queue* parse_file(FILE* fp);
bool is_part_of_word(char* s);
regex_t* get_word_regex(void);
void free_word_regex(void);

//  https://stackoverflow.com/questions/9642732/parsing-command-line-arguments
//  https://www.gnu.org/software/libc/manual/html_node/Argp-Example-3.html#Argp-Example-3
const char *argp_program_version = "AutoCheck 0.0.0";
const char *argp_program_bug_address = "riley.martine.0@gmail.com";
static char doc[] = "Looks for words in a file not in the dictionary, and prompts to replace them.";
static char args_doc[] = "[FILENAME]";
static struct argp_option options[] = {
    { "noprompt", 'n', 0, 0, "Do not prompt for replacements, just perform them.", 0},
    { "report", 'r', 0, 0, "Generate a report, but do not prompt for replacements.", 0},
    { "inplace", 'i', 0, 0, "Write fixes to the file in place.", 0},
    { 0 }
};

struct arguments {
    bool prompt, report, inplace;
    const char *input_file;
};

static error_t parse_opt(int key, char *arg, struct argp_state *state) {
    struct arguments *arguments = state->input;

    switch (key) {
        case 'n':
            arguments->prompt = false;
            break;
        case 'r':
            arguments->report = true;
            arguments->prompt = false;
            arguments->inplace = false;
            break;
        case 'i':
            arguments->inplace = true;
            break;
        case ARGP_KEY_ARG:
            if (state->arg_num >= 1) {
                argp_usage(state);
            }
            arguments->input_file = arg;
            break;
        case ARGP_KEY_END:
            if (state->arg_num < 1) {
                argp_usage(state);
            }
            break;
        default:
            return ARGP_ERR_UNKNOWN;
    }
    return 0;
}

static struct argp argp = {options, parse_opt, args_doc, doc, 0, 0, 0};


int main(int argc, char *argv[]) {
    struct arguments arguments;

    // default values for arguments
    arguments.prompt = true;
    arguments.report = false;
    arguments.inplace = false;
    arguments.input_file = "-";

    argp_parse(&argp, argc, argv, 0, 0, &arguments);

    printf("prompt: %d, report: %d, inplace: %d, file: %s\n", arguments.prompt, arguments.report, arguments.inplace, arguments.input_file);
    
    FILE* fp = fopen(arguments.input_file, "r");
    Queue* file_parts = parse_file(fp);
    fclose(fp);

    bool cur_is_word = is_part_of_word(peek(file_parts));
    while (! isEmpty(file_parts)) {
        if (cur_is_word) {
            if (is_trie_word(peek(file_parts))) {
                printf("%s", peek(file_parts));
            } else {
                printf("|%s|", peek(file_parts));
            }
        } else {
            printf("%s", peek(file_parts));
        }
        cur_is_word = !cur_is_word;
        pop(file_parts);
    }

    free_dict();
    clear(file_parts);
    free_word_regex();
    return 0;
}

regex_t* get_word_regex(void) {
    static regex_t* exp;
    
    if (exp == NULL) {
        exp = malloc(sizeof(regex_t));
        if ( 0 != (regcomp(exp, "[^a-zA-Z']", REG_EXTENDED))) {
            printf("regcomp() failed, returning nonzero.\n");
            exit(EXIT_FAILURE);
        }
    }

    return exp;

}

void free_word_regex(void) {
    free(get_word_regex());
}

bool is_part_of_word(char* s) {
    bool word = true;
    regex_t* exp = get_word_regex();

    if (! regexec(exp, s, 0, NULL, 0)) {
        // match is true
        word = false;
    }

    return word;
}

Queue* parse_file(FILE* fp) {
    Queue* queue = initQueue();

    char* token = calloc(128, sizeof(char)); 
    //for(int i = 0; i < 32; i++){
    //    token[i] = '\0';
    //}
    bool in_word; // Whether the current token is a word or non-word
    int index = 0; // the position within the current token to insert the next char

    char cur[2];
    cur[0] = (char) fgetc(fp);
    cur[1] = '\0';
    in_word = is_part_of_word(cur);
    bool flag = true;
    while(flag) {
        // printf("%s %d %d\n",cur, in_word, is_part_of_word(cur) );
        if (cur[0] == EOF) {
            if (index != 0) {
                push(queue, token);
            }
            free(token);
            flag = false;
        } else if (in_word && is_part_of_word(cur)) {
            token[index] = cur[0];
            ++index;
        } else if (!in_word && !is_part_of_word(cur)) {
            token[index] = cur[0];
            ++index;
        } else {
            // The token is complete
            if (index != 0) {
                // printf("%s\n", token);
                push(queue, token);
            }
            index = 0;
            free(token);
            token = calloc(128, sizeof(char)); 
            in_word = !in_word;
            token[index] = cur[0];
            ++index;
        }
        if (cur[0] != EOF) {
            cur[0] = (char) fgetc(fp);
        }

    }

    //printQueue(queue);
    return queue;
}
