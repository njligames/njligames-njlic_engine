/* -------- NJLI INLINE (BEGIN) -------- */

#if !defined(SWIGEMBIND)
%inline %{
GLfloat *newfv4(GLfloat a, GLfloat b, GLfloat c, GLfloat d)
{
  GLfloat *f = (GLfloat*) malloc(4 * sizeof(GLfloat));
  f[0] = a;
  f[1] = b;
  f[2] = c;
  f[3] = d;
  return f;
}
%}

%inline %{
void delfv(void *m)
{
    free(m);
}
%}
#endif

/* -------- NJLI INLINE (END) -------- */
