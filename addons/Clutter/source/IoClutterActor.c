#include "IoClutterActor.h"

/*** Initalisation functions ***/
IoTag *IoClutterActor_newTag(void *state) {
  IoTag *tag = IoTag_newWithName_("ClutterActor");

  IoTag_state_(tag, state);
  IoTag_freeFunc_(tag, (IoTagFreeFunc *)IoClutterActor_free);
  IoTag_cloneFunc_(tag, (IoTagCloneFunc *)IoClutterActor_rawClone);

  return tag;
}

IoClutterActor *IoClutterActor_proto(void *state) {
  IoObject *self = IoObject_new(state);
  IoObject_tag_(self, IoClutterActor_newTag(state));

  IoState_registerProtoWithFunc_(state, self, IoClutterActor_proto);

  {
    IoMethodTable methodTable[] = {
      {"isMapped",        IoClutterActor_isMapped},
      {"isRealized",      IoClutterActor_isRealized},
      {"isVisible",       IoClutterActor_isVisible},
      {"isReactive",      IoClutterActor_isReactive},

      {"show",            IoClutterActor_show},
      {"showAll",         IoClutterActor_showAll},
      {"hide",            IoClutterActor_hide},
      {"hideAll",         IoClutterActor_hideAll},
      {"realize",         IoClutterActor_realize},
      {"unrealize",       IoClutterActor_unrealize},
      {"paint",           IoClutterActor_paint},
      {"queueRedraw",     IoClutterActor_queueRedraw},
      {"queueRelayout",   IoClutterActor_queueRelayout},
      {"destroy",         IoClutterActor_destroy},
      {"event",           IoClutterActor_event},
      {"shouldPickPaint", IoClutterActor_shouldPickPaint},
      {"map",             IoClutterActor_map},
      {"unmap",           IoClutterActor_unmap},

      {"allocate",              IoClutterActor_allocate},
      {"allocatePrefferedSize", IoClutterActor_allocatePrefferedSize},
      {"allocateAvailableSize", IoClutterActor_allocateAvailableSize},
      {"allocationBox",         IoClutterActor_getAllocationBox},
      {"allocationGeometry",    IoClutterActor_getAllocationGeometry},

      {"getPreferredSize",      IoClutterActor_getPreferredSize},
      {"getPreferredWidth",     IoClutterActor_getPreferredWidth},
      {"getPreferredHeight",    IoClutterActor_getPreferredHeight},

      {"isPositionFixed",       IoClutterActor_getFixedPosition},
      {"setIsPositionFixed",    IoClutterActor_setFixedPosition},

      {"geometry",              IoClutterActor_getGeometry},
      {"setGeometry",           IoClutterActor_setGeometry},
      {"size",                  IoClutterActor_getSize},
      {"setSize",               IoClutterActor_setSize},
      {"position",              IoClutterActor_getPosition},
      {"setPosition",           IoClutterActor_setPosition},
      {"width",                 IoClutterActor_getWidth},
      {"setWidth",              IoClutterActor_setWidth},
      {"height",                IoClutterActor_getHeight},
      {"setHeight",             IoClutterActor_setHeight},
      {"x",                     IoClutterActor_getX},
      {"setX",                  IoClutterActor_setX},
      {"y",                     IoClutterActor_getY},
      {"setY",                  IoClutterActor_setY},

      {"moveBy",                IoClutterActor_moveBy},
      {"rotation",              IoClutterActor_getRotation},
      {"setRotation",           IoClutterActor_setRotation},
      {"zRotationGravity",      IoClutterActor_getZRotationGravity},
      {"setZRotationGravity",   IoClutterActor_setZRotationFromGravity},

      {"opacity",     IoClutterActor_getOpacity},
      {"setOpacity",  IoClutterActor_setOpacity},

      {"name",        IoClutterActor_getName},
      {"setName",     IoClutterActor_setName},
      {"gid",         IoClutterActor_getGid},

      {"clip",        IoClutterActor_getClip},
      {"setClip",     IoClutterActor_setClip},
      {"hasClip",     IoClutterActor_hasClip},
      {"removeClip",  IoClutterActor_removeClip},

      {"raise",         IoClutterActor_raise},
      {"lower",         IoClutterActor_lower},
      {"raiseToTop",    IoClutterActor_raiseToTop},
      {"lowerToBottom", IoClutterActor_lowerToBottom},

      {NULL, NULL}
    };
    IoObject_addMethodTable_(self, methodTable);
  }

  return self;
}

IoClutterActor *IoClutterActor_rawClone(IoClutterActor *proto) {
  IoClutterActor *self = IoObject_rawClonePrimitive(proto);
  return self;
}

IoClutterActor *IoClutterActor_new(void *state) {
  IoObject *proto = IoState_protoWithInitFunction_((IoState *)state, IoClutterActor_proto);
  return IOCLONE(proto);
}

IoClutterActor *IoClutterActor_newWithActor(void *state, ClutterActor *actor) {
  IoClutterActor *self = IoClutterActor_new(state);
  IoObject_setDataPointer_(self, actor);
  return self;
}

void IoClutterActor_free(IoClutterActor *self) {
  if(CLUTTER_IS_ACTOR(IOCACTOR(self)))
    clutter_actor_destroy(IOCACTOR(self));

  io_free(IoObject_dataPointer(self));
}

IoObject *IoMessage_locals_clutterActorArgAt_(IoMessage *self, IoObject *locals, int n) {
  IoObject *v = IoMessage_locals_valueArgAt_(self, locals, n);

  if(!ISCLUTTERACTOR(v)) {
    IoMessage_locals_numberArgAt_errorForType_(self, locals, n, "ClutterActor");
  }

  return v;
}

IO_METHOD(IoClutterActor, isMapped) {
  return IOBOOL(self, CLUTTER_ACTOR_IS_MAPPED(IOCACTOR(self)));
}

IO_METHOD(IoClutterActor, isRealized) {
  return IOBOOL(self, CLUTTER_ACTOR_IS_REALIZED(IOCACTOR(self)));
}

IO_METHOD(IoClutterActor, isVisible) {
  return IOBOOL(self, CLUTTER_ACTOR_IS_VISIBLE(IOCACTOR(self)));
}

IO_METHOD(IoClutterActor, isReactive) {
  return IOBOOL(self, CLUTTER_ACTOR_IS_REACTIVE(IOCACTOR(self)));
}

IO_METHOD(IoClutterActor, show) {
  fprintf(stderr, "In IoClutterActor_show\n");
  clutter_actor_show(IOCACTOR(self));
  fprintf(stderr, "Out IoClutterActor_show\n");
  return self;
}

IO_METHOD(IoClutterActor, showAll) {
  clutter_actor_show_all(IOCACTOR(self));
  return self;
}

IO_METHOD(IoClutterActor, hide) {
  clutter_actor_hide(IOCACTOR(self));
  return self;
}

IO_METHOD(IoClutterActor, hideAll) {
  clutter_actor_hide_all(IOCACTOR(self));
  return self;
}

IO_METHOD(IoClutterActor, realize) {
  clutter_actor_realize(IOCACTOR(self));
  return self;
}

IO_METHOD(IoClutterActor, unrealize) {
  clutter_actor_unrealize(IOCACTOR(self));
  return self;
}


IO_METHOD(IoClutterActor, paint) {
  clutter_actor_paint(IOCACTOR(self));
  return self;
}

IO_METHOD(IoClutterActor, queueRedraw) {
  clutter_actor_queue_redraw(IOCACTOR(self));
  return self;
}

IO_METHOD(IoClutterActor, queueRelayout) {
  clutter_actor_queue_relayout(IOCACTOR(self));
  return self;
}

IO_METHOD(IoClutterActor, destroy) {
  clutter_actor_destroy(IOCACTOR(self));
  return self;
}

//doc ClutterActor event(clutterEvent, capture)
IO_METHOD(IoClutterActor, event) {
  int success = clutter_actor_event(
    IOCACTOR(self),
    IOCEVENT(IoMessage_locals_clutterEventArgAt_(m, locals, 0)),
    IoMessage_locals_boolArgAt_(m, locals, 1));

  return IOBOOL(self, success);
}

IO_METHOD(IoClutterActor, shouldPickPaint) {
  return IOBOOL(self, clutter_actor_should_pick_paint(IOCACTOR(self)));
}

IO_METHOD(IoClutterActor, map) {
  clutter_actor_map(IOCACTOR(self));
  return self;
}

IO_METHOD(IoClutterActor, unmap) {
  clutter_actor_unmap(IOCACTOR(self));
  return self;
}

//doc ClutterActor allocate(clutterActorBox, absoluteOriginChanged)
IO_METHOD(IoClutterActor, allocate) {
  ClutterActorBox *actorBox = IOCABOX(IoMessage_locals_clutterActorBoxArgAt_(m, locals, 0));

  clutter_actor_allocate(
    IOCACTOR(self),
    actorBox,
    origin_changed_flags(IoMessage_locals_boolArgAt_(m, locals, 1))
  );

  return self;
}

/*doc ClutterActor allocateprefferedSize(originChanged)
If <code>originChanged</code> is <code>true</code>,
<code>CLUTTER_ABSOLUTE_ORIGIN_CHANGED</code> flag will be used. */
IO_METHOD(IoClutterActor, allocatePrefferedSize) {
  clutter_actor_allocate_preferred_size(
    IOCACTOR(self),
    origin_changed_flags(IoMessage_locals_boolArgAt_(m, locals, 0))
  );

  return self;
}

//doc ClutterActor allocateAvailableSize(x, y, width, height, originChanged)
IO_METHOD(IoClutterActor, allocateAvailableSize) {
  float x = IoMessage_locals_floatArgAt_(m, locals, 0),
        y = IoMessage_locals_floatArgAt_(m, locals, 1),
        w = IoMessage_locals_floatArgAt_(m, locals, 2),
        h = IoMessage_locals_floatArgAt_(m, locals, 3);
  int   origin_changed = IoMessage_locals_boolArgAt_(m, locals, 4);

  clutter_actor_allocate_available_size(IOCACTOR(self), x, y, w, h, origin_changed);
  return self;
}

IO_METHOD(IoClutterActor, getAllocationBox) {
  ClutterActorBox actorBox = { 0, };
  clutter_actor_get_allocation_box(IOCACTOR(self), &actorBox);

  return IoClutterActorBox_newWithActorBox(IOSTATE, &actorBox);
}

IO_METHOD(IoClutterActor, getAllocationGeometry) {
  ClutterGeometry geom = { 0, };
  clutter_actor_get_allocation_geometry(IOCACTOR(self), &geom);
  return clutter_geometry_to_ioObject(IOSTATE, self, &geom);
}

IO_METHOD(IoClutterActor, getAllocationVertices) {
  ClutterVertex vertices[4] = {};
  IoList *result = IoList_new(IOSTATE);

  if(IoMessage_argCount(m) > 0) {
    ClutterActor *ancestor = IOCACTOR(IoMessage_locals_clutterActorArgAt_(m, locals, 0));
    clutter_actor_get_allocation_vertices(IOCACTOR(self), ancestor, vertices);
  } else {
    clutter_actor_get_allocation_vertices(IOCACTOR(self), NULL, vertices);
  }

  IoList_rawAppend_(result, IoClutterVertex_newWithVertex(IOSTATE, &vertices[0]));
  IoList_rawAppend_(result, IoClutterVertex_newWithVertex(IOSTATE, &vertices[1]));
  IoList_rawAppend_(result, IoClutterVertex_newWithVertex(IOSTATE, &vertices[2]));
  IoList_rawAppend_(result, IoClutterVertex_newWithVertex(IOSTATE, &vertices[3]));

  return result;
}

IO_METHOD(IoClutterActor, getPreferredSize) {
  float min_width = 0,
        min_height = 0,
        natural_width = 0,
        natural_height = 0;
  IoObject *p_size = IoObject_new(IOSTATE);

  clutter_actor_get_preferred_size(
    IOCACTOR(self),
    &min_width,     &min_height,
    &natural_width, &natural_height
  );

  IoObject_setSlot_to_(p_size, IOSYMBOL("minWidth"),       IONUMBER(min_width));
  IoObject_setSlot_to_(p_size, IOSYMBOL("minHeight"),      IONUMBER(min_height));
  IoObject_setSlot_to_(p_size, IOSYMBOL("naturalHeight"),  IONUMBER(natural_width));
  IoObject_setSlot_to_(p_size, IOSYMBOL("naturalHeight"),  IONUMBER(natural_height));

  return p_size;
}

IO_METHOD(IoClutterActor, getPreferredWidth) {
  float for_height    = IoMessage_locals_floatArgAt_(m, locals, 0),
        min_width     = 0,
        natural_width = 0;

  clutter_actor_get_preferred_width(
    IOCACTOR(self),
    for_height, &min_width, &natural_width
  );

  IoObject *result = IoObject_new(IOSTATE);
  IoObject_setSlot_to_(result, IOSYMBOL("minWidth"),     IONUMBER(min_width));
  IoObject_setSlot_to_(result, IOSYMBOL("naturalWidth"), IONUMBER(natural_width));

  return result;
}

IO_METHOD(IoClutterActor, getPreferredHeight) {
  float for_width       = IoMessage_locals_floatArgAt_(m, locals, 0),
        min_height      = 0,
        natural_height  = 0;

  clutter_actor_get_preferred_height(
    IOCACTOR(self),
    for_width, &min_height, &natural_height
  );

  IoObject *result = IoObject_new(IOSTATE);
  IoObject_setSlot_to_(result, IOSYMBOL("minHeight"),      IONUMBER(min_height));
  IoObject_setSlot_to_(result, IOSYMBOL("naturalHeight"),  IONUMBER(natural_height));

  return result;
}

IO_METHOD(IoClutterActor, getFixedPosition) {
  return IOBOOL(self, clutter_actor_get_fixed_position_set(IOCACTOR(self)));
}

IO_METHOD(IoClutterActor, setFixedPosition) {
  int state = IoMessage_locals_boolArgAt_(m, locals, 0);
  clutter_actor_set_fixed_position_set(IOCACTOR(self), state);
  return self;
}

IO_METHOD(IoClutterActor, getGeometry) {
  ClutterGeometry geometry;
  clutter_actor_get_geometry(IOCACTOR(self), &geometry);
  return clutter_geometry_to_ioObject(IOSTATE, self, &geometry);
}

IO_METHOD(IoClutterActor, setGeometry) {
  ClutterGeometry geometry = { 0, 0, 0, 0, };
  geometry.x       = IoMessage_locals_intArgAt_(m, locals, 0);
  geometry.y       = IoMessage_locals_intArgAt_(m, locals, 1);
  geometry.width   = IoMessage_locals_intArgAt_(m, locals, 2);
  geometry.height  = IoMessage_locals_intArgAt_(m, locals, 3);

  clutter_actor_set_geometry(IOCACTOR(self), &geometry);
  return self;
}

IO_METHOD(IoClutterActor, getSize) {
  float width = 0,
        height = 0;
  clutter_actor_get_size(IOCACTOR(self), &width, &height);

  IoObject *size = IoObject_new(IOSTATE);
  IoObject_setSlot_to_(size, IOSYMBOL("width"), IONUMBER(width));
  IoObject_setSlot_to_(size, IOSYMBOL("height"), IONUMBER(height));

  return size;
}

IO_METHOD(IoClutterActor, setSize) {
  float width   = IoMessage_locals_floatArgAt_(m, locals, 0),
        height  = IoMessage_locals_floatArgAt_(m, locals, 1);

  clutter_actor_set_size(IOCACTOR(self), width, height);
  return self;
}

IO_METHOD(IoClutterActor, getPosition) {
  float x = 0,
        y = 0;
  clutter_actor_get_size(IOCACTOR(self), &x, &y);

  IoObject *size = IoObject_new(IOSTATE);
  IoObject_setSlot_to_(size, IOSYMBOL("x"), IONUMBER(x));
  IoObject_setSlot_to_(size, IOSYMBOL("y"), IONUMBER(y));

  return size;
}

IO_METHOD(IoClutterActor, setPosition) {
  float x  = IoMessage_locals_floatArgAt_(m, locals, 0),
        y  = IoMessage_locals_floatArgAt_(m, locals, 1);

  clutter_actor_set_size(IOCACTOR(self), x, y);
  return self;
}

IO_METHOD(IoClutterActor, getWidth) {
  return IONUMBER(clutter_actor_get_width(IOCACTOR(self)));
}

IO_METHOD(IoClutterActor, setWidth) {
  clutter_actor_set_width(IOCACTOR(self), IoMessage_locals_floatArgAt_(m, locals, 0));
  return self;
}

IO_METHOD(IoClutterActor, getHeight) {
  return IONUMBER(clutter_actor_get_height(IOCACTOR(self)));
}

IO_METHOD(IoClutterActor, setHeight) {
  clutter_actor_set_height(IOCACTOR(self), IoMessage_locals_floatArgAt_(m, locals, 0));
  return self;
}

IO_METHOD(IoClutterActor, getX) {
  return IONUMBER(clutter_actor_get_x(IOCACTOR(self)));
}

IO_METHOD(IoClutterActor, setX) {
  clutter_actor_set_x(IOCACTOR(self), IoMessage_locals_floatArgAt_(m, locals, 0));
  return self;
}

IO_METHOD(IoClutterActor, getY) {
  return IONUMBER(clutter_actor_get_y(IOCACTOR(self)));
}

IO_METHOD(IoClutterActor, setY) {
  clutter_actor_set_y(IOCACTOR(self), IoMessage_locals_floatArgAt_(m, locals, 0));
  return self;
}

IO_METHOD(IoClutterActor, moveBy) {
  float dx = IoMessage_locals_floatArgAt_(m, locals, 0),
        dy = IoMessage_locals_floatArgAt_(m, locals, 1);

  clutter_actor_move_by(IOCACTOR(self), dx, dy);
  return self;
}

IO_METHOD(IoClutterActor, getRotation) {
  ClutterRotateAxis axis = IoMessage_locals_intArgAt_(m, locals, 0);
  float x = 0,
        y = 0,
        z = 0;
  double angle = clutter_actor_get_rotation(IOCACTOR(self), axis, &x, &y, &z);

  IoObject *rotation = IoObject_new(IOSTATE);
  IoObject_setSlot_to_(rotation, IOSYMBOL("x"),     IONUMBER(x));
  IoObject_setSlot_to_(rotation, IOSYMBOL("y"),     IONUMBER(y));
  IoObject_setSlot_to_(rotation, IOSYMBOL("z"),     IONUMBER(z));
  IoObject_setSlot_to_(rotation, IOSYMBOL("angle"), IONUMBER(angle));

  return rotation;
}

IO_METHOD(IoClutterActor, setRotation) {
  ClutterRotateAxis axis = IoMessage_locals_intArgAt_(m, locals, 0);
  double angle  = IoMessage_locals_doubleArgAt_(m, locals, 1);
  float x       = IoMessage_locals_floatArgAt_(m, locals, 2),
        y       = IoMessage_locals_floatArgAt_(m, locals, 3),
        z       = IoMessage_locals_floatArgAt_(m, locals, 4);

  clutter_actor_set_rotation(IOCACTOR(self), axis, angle, x, y, z);
  return self;
}

IO_METHOD(IoClutterActor, getZRotationGravity) {
  return IONUMBER(clutter_actor_get_z_rotation_gravity(IOCACTOR(self)));
}

IO_METHOD(IoClutterActor, setZRotationFromGravity) {
  clutter_actor_set_z_rotation_from_gravity(
    IOCACTOR(self),
    IoMessage_locals_doubleArgAt_(m, locals, 0),
    IoMessage_locals_intArgAt_(m, locals, 1)
  );
  return self;
}

IO_METHOD(IoClutterActor, isRotated) {
  return IOBOOL(self, clutter_actor_is_rotated(IOCACTOR(self)));
}

IO_METHOD(IoClutterActor, getOpacity) {
  return IONUMBER(clutter_actor_get_opacity(IOCACTOR(self)));
}

IO_METHOD(IoClutterActor, setOpacity) {
  clutter_actor_set_opacity(
    IOCACTOR(self),
    IoMessage_locals_intArgAt_(m, locals, 0)
  );
  return self;
}

IO_METHOD(IoClutterActor, getName) {
  return IOSYMBOL(clutter_actor_get_name(IOCACTOR(self)));
}

IO_METHOD(IoClutterActor, setName) {
  clutter_actor_set_name(
    IOCACTOR(self),
    IoMessage_locals_cStringArgAt_(m, locals, 0)
  );
  return self;
}

IO_METHOD(IoClutterActor, getGid) {
  return IONUMBER(clutter_actor_get_gid(IOCACTOR(self)));
}

IO_METHOD(IoClutterActor, getClip) {
  float xoff    = 0,
        yoff    = 0,
        width   = 0,
        height  = 0;
  IoObject *result = IoObject_new(IOSTATE);

  clutter_actor_get_clip(IOCACTOR(self), &xoff, &yoff, &width, &height);
  IoObject_setSlot_to_(result, IOSYMBOL("xOff"),    IONUMBER(xoff));
  IoObject_setSlot_to_(result, IOSYMBOL("yOff"),    IONUMBER(yoff));
  IoObject_setSlot_to_(result, IOSYMBOL("width"),   IONUMBER(width));
  IoObject_setSlot_to_(result, IOSYMBOL("height"),  IONUMBER(height));

  return result;
}

IO_METHOD(IoClutterActor, setClip) {
  clutter_actor_set_clip(
    IOCACTOR(self),
    IoMessage_locals_floatArgAt_(m, locals, 0),
    IoMessage_locals_floatArgAt_(m, locals, 1),
    IoMessage_locals_floatArgAt_(m, locals, 2),
    IoMessage_locals_floatArgAt_(m, locals, 3)
  );
  return self;
}

IO_METHOD(IoClutterActor, hasClip) {
  return IOBOOL(self, clutter_actor_has_clip(IOCACTOR(self)));
}

IO_METHOD(IoClutterActor, removeClip) {
  clutter_actor_remove_clip(IOCACTOR(self));
  return self;
}

IO_METHOD(IoClutterActor, getParent) {
  return IoClutterActor_newWithActor(
    IOSTATE,
    clutter_actor_get_parent(IOCACTOR(self))
  );
}

IO_METHOD(IoClutterActor, setParent) {
  clutter_actor_set_parent(
    IOCACTOR(self),
    IOCACTOR(IoMessage_locals_clutterActorArgAt_(m, locals, 0))
  );
  return self;
}

IO_METHOD(IoClutterActor, reparent) {
  clutter_actor_reparent(
    IOCACTOR(self),
    IOCACTOR(IoMessage_locals_clutterActorArgAt_(m, locals, 0))
  );
  return self;
}

IO_METHOD(IoClutterActor, unparent) {
  clutter_actor_unparent(IOCACTOR(self));
  return self;
}

IO_METHOD(IoClutterActor, raise) {
  clutter_actor_raise(
    IOCACTOR(self),
    IOCACTOR(IoMessage_locals_clutterActorArgAt_(m, locals, 0))
  );

  return self;
}

IO_METHOD(IoClutterActor, lower) {
  clutter_actor_lower(
    IOCACTOR(self),
    IOCACTOR(IoMessage_locals_clutterActorArgAt_(m, locals, 0))
  );

  return self;
}

IO_METHOD(IoClutterActor, raiseToTop) {
  clutter_actor_raise_top(IOCACTOR(self));

  return self;
}

IO_METHOD(IoClutterActor, lowerToBottom) {
  clutter_actor_lower_bottom(IOCACTOR(self));

  return self;
}

IO_METHOD(IoClutterActor, getStage) {
  return IoClutterActor_newWithActor(
    IOSTATE,
    clutter_actor_get_stage(IOCACTOR(self))
  );
}