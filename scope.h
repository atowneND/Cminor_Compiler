void scope_enter(void);
void scope_exit(void);
void scope_bind(const char *name, struct symbol *s);
struct symbol *scope_lookup(const char *name);
