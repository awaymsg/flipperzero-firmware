#include "subghz_debruijn.h"

#define MAXBITCOUNT 3

static void DeBruijnGen(uint32_t t, uint32_t p, DeBruijnData* debruijndata) {
    uint32_t i,j;

    if (t > debruijndata->n) {
        if (debruijndata->n % p == 0) {
            for (i = 1; i <= p; i++) {
                debruijndata->byte = debruijndata->byte | debruijndata->a[i] << debruijndata->bitcount;

                if (debruijndata->bitcount == 0) {
                    string_cat_printf(debruijndata->debruijnstr, "%X", debruijndata->byte);
                    debruijndata->bitcount = MAXBITCOUNT + 1;
                    debruijndata->byte = 0;
                }

                debruijndata->bitcount--;
            }
        }
        return;
    }

    for (j = debruijndata->a[t - p]; j < 2; j++) {
        debruijndata->a[t] = j;
        if (j == debruijndata->a[t - p]) {
            DeBruijnGen(t + 1, p, debruijndata);
        } else {
            DeBruijnGen(t + 1, t, debruijndata);
        }
    }

    if (t == 1 && p == 1) { // on base condition
        if (debruijndata->bitcount != MAXBITCOUNT) {
            string_cat_printf(debruijndata->debruijnstr, "%X", debruijndata->byte);
        }

        uint8_t extra = debruijndata->n / 4;
        if (debruijndata->n % 4 > 0) {
            extra++;
        }

        for (uint8_t i = 0; i < extra; i++) {
            string_push_back(debruijndata->debruijnstr, '0');
        }
    }
}

// NOTE: we do not have to generate this, but are doing it for fun. it would be much more
//       efficient to just store the debruijn sequence hex strings and pull them up
void DeBruijn(uint8_t codelength, string_t outputstr) {
    DeBruijnData* debruijndata = malloc(sizeof(DeBruijnData));
    string_init(debruijndata->debruijnstr);
    debruijndata->a[0] = 0;
    debruijndata->n = codelength;
    debruijndata->bitcount = MAXBITCOUNT;
    debruijndata->byte = 0;

    DeBruijnGen(1, 1, debruijndata);
    string_set(outputstr, debruijndata->debruijnstr);

    string_clear(debruijndata->debruijnstr);
    free(debruijndata);
    return;
}