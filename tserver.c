#include "tserver.h"

/* 
 * forward definitions
 */
G_DEFINE_TYPE (TServer, tserver, G_TYPE_OBJECT);
/*
/* forward declarations of default virtual methods 
 */

static void
tserver_dispose (GObject *gobject)
{
  TServer *self = TSERVER (gobject);

  /* 
   * In dispose, you are supposed to free all types referenced from this
   * object which might themselves hold a reference to self. Generally,
   * the most simple solution is to unref all members on which you own a 
   * reference.
   */

  /* Chain up to the parent class */
  G_OBJECT_CLASS (tserver_parent_class)->dispose (gobject);
}

static void
tserver_finalize (GObject *gobject)
{
  TServer *self = TSERVER (gobject);

  /* Chain up to the parent class */
  G_OBJECT_CLASS (tserver_parent_class)->finalize (gobject);
}

static void
tserver_init (TServer *self)
{
  /* initialize all public and private members to reasonable default values. */

  /* Default implementations for virtual methods 
   * For pure-virtual functions, set these to NULL
   */
}
void tserver_TServer(TServer* self)
{
    g_return_if_fail (IS_TSERVER (self));
    
}
void tserver_TServer(TServer* self, const TServer& other)
{
    g_return_if_fail (IS_TSERVER (self));
    
}
void tserver_~TServer(TServer* self)
{
    g_return_if_fail (IS_TSERVER (self));
    
}
TServer& tserver_operator=(TServer* self, const TServer& other)
{
    g_return_if_fail (IS_TSERVER (self));
    
}
bool tserver_operator==(TServer* self, const TServer& other)
{
    g_return_if_fail (IS_TSERVER (self));
    
}
bool tserver_operator!=(TServer* self, const TServer& other)
{
    g_return_if_fail (IS_TSERVER (self));
    
}
#include "tserver.h"


#define TSERVER_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE ((obj), TYPE_TSERVER, TServerPrivate))

struct _TServerPrivate
{
    /* private members */
};

/* 
 * forward definitions
 */
G_DEFINE_TYPE (TServer, tserver, G_TYPE_OBJECT);

/*
/* forward declarations of default virtual methods 
 */

enum {
    PROP_0,
    N_PROPERTIES
};

static GParamSpec *obj_properties[N_PROPERTIES] = { NULL, };
static void
tserver_set_property (GObject      *object,
                        guint         property_id,
                        const GValue *value,
                        GParamSpec   *pspec)
{
    TServer *self = TSERVER (object);
    switch (property_id)
    {
        default:
            G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
            break;
    }
}

static void
tserver_get_property (GObject      *object,
                        guint         property_id,
                        GValue       *value,
                        GParamSpec   *pspec)
{
    TServer *self = TSERVER (object);
    switch (property_id)
    {
        default:
            G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
            break;
    }
}

static void
tserver_class_init (TServerClass *klass)
{
  g_type_class_add_private (klass, sizeof (TServerPrivate));

  GObjectClass *gobject_class = G_OBJECT_CLASS (klass);
  gobject_class->set_property = tserver_set_property;
  gobject_class->get_property = tserver_get_property;

  g_object_class_install_properties (gobject_class,
                                     N_PROPERTIES,
                                     obj_properties);
}

static void
tserver_dispose (GObject *gobject)
{
  TServer *self = TSERVER (gobject);

  /* 
   * In dispose, you are supposed to free all types referenced from this
   * object which might themselves hold a reference to self. Generally,
   * the most simple solution is to unref all members on which you own a 
   * reference.
   */

  /* Chain up to the parent class */
  G_OBJECT_CLASS (tserver_parent_class)->dispose (gobject);
}

static void
tserver_finalize (GObject *gobject)
{
  TServer *self = TSERVER (gobject);

  /* Chain up to the parent class */
  G_OBJECT_CLASS (tserver_parent_class)->finalize (gobject);
}

static void
tserver_init (TServer *self)
{
  self->priv = TSERVER_GET_PRIVATE (self);

  /* initialize all public and private members to reasonable default values. */

  /*
   * Default implementations for virtual methods 
   * For pure-virtual functions, set these to NULL
   */
}
void tserver_TServer(TServer* self)
{
    g_return_if_fail (IS_TSERVER (self));
}
void tserver_TServer(TServer* self, const TServer& other)
{
    g_return_if_fail (IS_TSERVER (self));
}
void tserver_~TServer(TServer* self)
{
    g_return_if_fail (IS_TSERVER (self));
}
TServer& tserver_operator=(TServer* self, const TServer& other)
{
    g_return_if_fail (IS_TSERVER (self));
}
bool tserver_operator==(TServer* self, const TServer& other)
{
    g_return_if_fail (IS_TSERVER (self));
}
bool tserver_operator!=(TServer* self, const TServer& other)
{
    g_return_if_fail (IS_TSERVER (self));
}
