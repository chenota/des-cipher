#include <argp.h>
#include <string.h>
#include <stdio.h>
#include "des.h"

const char *argp_program_version = "des 1.0.0";
static char doc[] = "DES cipher encoder and decoder";
static char args_doc[] = "TEXT KEY";

static struct argp_option options[] = {
    { "encrypt", 'e', 0, 0, "Run in encrypt mode" },
    { "decrypt", 'd', 0, 0, "Run in decrypt mode" },
    { "hex", 'h', 0, 0, "Use hexadecimal input" },
    { "ascii", 'a', 0, 0, "Use ASCII input" }
};

struct arguments {
    enum { ENCRYPT, DECRYPT, NONE } mode;
    enum { HEX, ASCII } input;
    char *args[2];
};

static error_t parse_opt(int key, char *arg, struct argp_state *state) {
    struct arguments *arguments = state->input;
    switch (key) {
        case 'e' : arguments->mode = ENCRYPT; break;
        case 'd' : arguments->mode = DECRYPT; break;
        case 'h' : arguments->input = HEX; break;
        case 'a' : arguments->input = ASCII; break;
        case ARGP_KEY_ARG:
            if(state->arg_num >= 2) argp_usage(state);
            arguments->args[state->arg_num] = arg;
            break;
        case ARGP_KEY_END :
            if(arguments->mode == NONE) {
                argp_failure(state, 1, 0, "Required -e or -d. See --help for more information");
                return ARGP_ERR_UNKNOWN;
            }
            if(state->arg_num < 2) {
                argp_failure(state, 1, 0, "Required text and key. See --help for more information");
            }
            break;
        default : return ARGP_ERR_UNKNOWN;
    }
    return 0;
}

static struct argp argp = { options, parse_opt, args_doc, doc, 0, 0, 0 };

int main(int argc, char *argv[]) {
    // Do argument parsing
    struct arguments arguments;
    arguments.mode = NONE;
    arguments.input = ASCII;
    argp_parse(&argp, argc, argv, 0, 0, &arguments);
    // Get pointers to text and key
    char *text = arguments.args[0];
    char *key = arguments.args[1];
    // Get length of text and key (should be no more than 16 bits, so restrict to a couple over that)
    size_t textLen = strnlen(text, 18);
    size_t keyLen = strnlen(key, 18);
    // Validate length of text and key
    switch(arguments.input) {
        case ASCII:
            if(textLen > 8 || keyLen > 8) {
                perror("Text and Key length must be no more than eight characters");
                exit(1);
            }
        case HEX:
            if(textLen > 16 || keyLen > 16) {
                perror("Text and Key length must be no more than sixteen characters");
                exit(1);
            }
    }
    return 0;
}