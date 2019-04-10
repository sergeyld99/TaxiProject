/* inclusion guard */
#ifndef __TSERVER_H__
#define __TSERVER_H__

#include <glib-2.0/gobject/gobject.h>
//#include <glib-object.h>
/*
 * Potentially, include other headers on which this header depends.
 */

/*
 * Type macros.
 */
#define TYPE_TSERVER                  (tserver_get_type ())
#define TSERVER(obj)                  (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_TSERVER, TServer))
#define IS_TSERVER(obj)               (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_TSERVER))
#define TSERVER_CLASS(klass)          (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_TSERVER, TServerClass))
#define IS_TSERVER_CLASS(klass)       (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_TSERVER))
#define TSERVER_GET_CLASS(obj)        (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_TSERVER, TServerClass))

typedef struct _TServer       TServer;
typedef struct _TServerClass   TServerClass;

struct _TServer
{
  GObject parent_instance;

  /* instance members */
};

struct _TServerClass
{
  GObjectClass parent_class;
  /* class members */
};

/* used by TYPE_TSERVER */
GType tserver_get_type (void);

/*
 * Method definitions.
 */
void tserver_TServer(TServer* self);
void tserver_TServer(TServer* self, const TServer& other);
void tserver_~TServer(TServer* self);
TServer& tserver_operator=(TServer* self, const TServer& other);
bool tserver_operator==(TServer* self, const TServer& other);
bool tserver_operator!=(TServer* self, const TServer& other);

#endif /* __TSERVER_H__ */
/* inclusion guard */
#ifndef __TSERVER_H__
#define __TSERVER_H__

#include <glib-2.0/gobject/gobject.h>
//#include <glib-object.h>
/*
 * Potentially, include other headers on which this header depends.
 */

/*
 * Type macros.
 */
#define TYPE_TSERVER                  (tserver_get_type ())
#define TSERVER(obj)                  (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_TSERVER, TServer))
#define IS_TSERVER(obj)               (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_TSERVER))
#define TSERVER_CLASS(klass)          (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_TSERVER, TServerClass))
#define IS_TSERVER_CLASS(klass)       (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_TSERVER))
#define TSERVER_GET_CLASS(obj)        (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_TSERVER, TServerClass))

typedef struct _TServer       TServer;
typedef struct _TServerClass   TServerClass;
typedef struct _TServerPrivate   TServerPrivate;

struct _TServer
{
  GObject parent_instance;

  /*< private >*/
  TServerPrivate *priv;
};

struct _TServerClass
{
  GObjectClass parent_class;
  /* class members */
};

/* used by TYPE_TSERVER */
GType tserver_get_type (void);

/*
 * Method definitions.
 */
void tserver_TServer(TServer* self);
void tserver_TServer(TServer* self, const TServer& other);
void tserver_~TServer(TServer* self);
TServer& tserver_operator=(TServer* self, const TServer& other);
bool tserver_operator==(TServer* self, const TServer& other);
bool tserver_operator!=(TServer* self, const TServer& other);

#endif /* __TSERVER_H__ */
