#include<cstdio>
#include <cstdlib>
#include <cstring>
#include <bits/stdc++.h>
#include<cmath>
#include<argp.h>
#include"ceMmDateTime.h"
using namespace ce;
using namespace std;

/* Program documentation. */
static char doc[] =
        "Argp example #3 -- a program with options and arguments using argp";

/* A description of the arguments we accept. */
static char args_doc[] = "ARG1 ARG2";

/* The options we understand. */
static struct argp_option options[] = {
        {"now",  'n', 0,      0,  "Today Burmese date in Myanmar language" },
        {"eng",  'e', 0,      0,  "Today Burmese date in English language" },
        { 0 }
};

/* Used by main to communicate with parse_opt. */
struct arguments
{
    char *args[2];                /* arg1 & arg2 */
    int now;
    int eng;
};

map<string, string> transliterate = {
        {"0", "၁"},
        {"1", "၁"},
        {"2", "၂"},
        {"3", "၃"},
        {"4", "၄"},
        {"5", "၅"},
        {"6", "၆"},
        {"7", "၇"},
        {"8", "၈"},
        {"9", "၉"},
        {"Tazaungmon", "တန်ဆောင်မုန်း"},
        {"Waning", "လဆုတ်"}
};

static std::string translate (std::string sentence)
{
    std::string str=sentence;
    for( auto const&[key, val] : transliterate )
    {
        size_t index = 0;
        while (true) {
            /* Locate the substring to replace. */
            index = str.find(key, index);
            if (index == std::string::npos) break;

            /* Make the replacement. */
            str.replace(index, key.length(), val);

            /* Advance index forward so the next iteration doesn't pick it up as well. */
            index += key.length();
        }
    }
    return str;
}

static void output(arguments arguments)
{
    ceMmDateTime dt;
    if(arguments.now) {
        if(arguments.eng) {
            printf("%s \n", dt.ToMString().c_str());
        } else {
            printf("%s \n", translate(dt.ToMString()).c_str());
        }
    }
}

/* Parse a single option. */
static error_t
parse_opt (int key, char *arg, struct argp_state *state)
{
    /* Get the input argument from argp_parse, which we
     know is a pointer to our arguments structure. */
    struct arguments *arguments = static_cast<struct arguments *>(state->input);

    switch (key)
    {
        case 'n':
            arguments->now = 1;
            break;
        case 'e':
            arguments->eng = 1;
            break;
        default:
            return ARGP_ERR_UNKNOWN;
    }


    return 0;
}

/* Our argp parser. */
static struct argp argp = { options, parse_opt, args_doc, doc };

int
main(int argc, char **argv)
{
    struct arguments arguments;
    arguments.now = 1;
    arguments.eng = 0;

    /* Parse our arguments; every option seen by parse_opt will
       be reflected in arguments. */
    argp_parse(&argp, argc, argv, 0, 0, &arguments);

    output(arguments);

    exit (0);
}