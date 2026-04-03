#include <stdlib.h>
#include <string.h>
#include "store.h"

/* Initialise le store */
void store_init(store_t *st)
{
if (st)
st->head = NULL;
}

/* Crée un node */
static node_t *node_create(session_t *s)
{
node_t *n = malloc(sizeof(*n));
if (!n)
return NULL;

n->sess = s;
n->next = NULL;

return n;
}

/* Ajoute une session */
int store_add(store_t *st, session_t *s)
{
node_t *n, *cur;

if (!st || !s || !s->id)
return 0;

/* Vérifie doublon */
cur = st->head;
while (cur) {
if (cur->sess && cur->sess->id &&
strcmp(cur->sess->id, s->id) == 0)
return 0;
cur = cur->next;
}

n = node_create(s);
if (!n)
return 0;

/* insertion en tête */
n->next = st->head;
st->head = n;

return 1;
}

/* Récupère une session */
session_t *store_get(store_t *st, const char *id)
{
node_t *cur;

if (!st || !id)
return NULL;

cur = st->head;
while (cur) {
if (cur->sess && cur->sess->id &&
strcmp(cur->sess->id, id) == 0)
return cur->sess;

cur = cur->next;
}

return NULL;
}

/* Supprime une session */
int store_delete(store_t *st, const char *id, session_t **out)
{
node_t *cur, *prev;

if (!st || !id)
return 0;

prev = NULL;
cur = st->head;

while (cur) {
if (cur->sess && cur->sess->id &&
strcmp(cur->sess->id, id) == 0) {

/* unlink */
if (prev)
prev->next = cur->next;
else
st->head = cur->next;

/* optionnel : récupérer la session */
if (out)
*out = cur->sess;
else
session_destroy(cur->sess);

free(cur);
return 1;
}

prev = cur;
cur = cur->next;
}

return 0;
}

/* Détruit tout le store */
void store_destroy(store_t *st)
{
node_t *cur, *next;

if (!st)
return;

cur = st->head;
while (cur) {
next = cur->next;

/* Le store possède la session → on free */
session_destroy(cur->sess);

free(cur);
cur = next;
}

st->head = NULL;
}
