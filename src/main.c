#include <argp.h>
#include "des.h"

const char *argp_program_version = "des 1.0.0";
static char doc[] = "DES cipher encoder and decoder";
static char args_doc[] = "text key";

static struct argp_option options[] = {
    { "encrypt", 'e', 0, 0, "Run in encrypt mode" },
    { "decrypt", 'd', 0, 0, "Run in decrypt mode" }
};

struct arguments {
    enum { ENCRYPT, DECRYPT, NONE } mode;
};

static error_t parse_opt(int key, char *arg, struct argp_state *state) {
    struct arguments *arguments = state->input;
    switch (key) {
        case 'e' : arguments->mode = ENCRYPT; break;
        case 'd' : arguments->mode = DECRYPT; break;
        case ARGP_KEY_END :
            if(arguments->mode == NONE) {
                argp_failure(state, 1, 0, "Required -e or -d. See --help for more information.");
                return ARGP_ERR_UNKNOWN;
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
    argp_parse(&argp, argc, argv, 0, 0, &arguments);
    return 0;
}