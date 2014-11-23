#include "shellinford_fm_index.h"

#ifdef __cplusplus
extern "C" {
#endif
#include "EXTERN.h"
#include "perl.h"
#include "XSUB.h"
#ifdef __cplusplus
}
#endif

#ifdef vform
#undef vform
#endif

#include "ppport.h"
using namespace std;
using namespace shellinford;

MODULE = Shellinford		PACKAGE = Shellinford		

fm_index *
fm_index::new()
CODE:
  fm_index *t = new fm_index();
  RETVAL = t;
OUTPUT:
  RETVAL

void
fm_index::DESTROY()

void
fm_index::clear()
CODE:
  THIS->clear();

void
fm_index::push_back(doc)
char *doc
CODE:
  THIS->push_back(doc);

void
fm_index::build()
CODE:
  THIS->build();

long
fm_index::docsize()
CODE:
  RETVAL = THIS->docsize();
OUTPUT:
  RETVAL

HV *
fm_index::search(key)
char *key
CODE:
  map<uint64_t, uint64_t> dids;
  THIS->search(key, dids);

  HV *hv = (HV *)sv_2mortal((SV *)newHV());
  map<uint64_t, uint64_t>::const_iterator i = dids.begin();
  map<uint64_t, uint64_t>::const_iterator e = dids.end();
  char id[40];
  while (i != e) {
    sprintf(id, "%llu", i->first);
    SV *sv_tf = sv_2mortal(newSVuv(i->second));
    SvREFCNT_inc(sv_tf);
    if (!hv_store(hv, id, strlen(id), sv_tf, 0)) {
      SvREFCNT_dec(sv_tf);
    }
    i++;
  }
  RETVAL = hv;
OUTPUT:
  RETVAL

SV *
fm_index::get_document(did)
long did
CODE:
  string doc = THIS->get_document(did);
  SV     *sv = newSVpv(doc.c_str(), doc.length());
  RETVAL = sv;
OUTPUT:
  RETVAL

int
fm_index::write(filename)
char *filename
CODE:
  RETVAL = 1;
  try {
    THIS->write(filename);
  } catch (const char *err) {
    RETVAL = 0;
  }
OUTPUT:
  RETVAL

int
fm_index::read(filename)
char *filename
CODE:
  RETVAL = 1;
  try {
    THIS->read(filename);
  } catch (const char *err) {
    RETVAL = 0;
  }
OUTPUT:
  RETVAL

