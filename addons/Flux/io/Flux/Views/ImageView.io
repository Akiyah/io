
ImageView := View clone do(
	position setX(0) setY(0)
	size setWidth(100) setHeight(24)
	newSlot("delegate")
	newSlot("image")


	init := method(
		resend
		image = Image clone
	)

	sizeToImage := method(
		if(image, size setWidth(image width) setHeight(image height))
		self
	)
	
	draw := method(
		if(image, drawProportional)
	)
	
	drawColor := method(
		glColor4d(1,1,1,1)
	)
	
	translateToPlacement := method(
        wr := width / image originalWidth
		hr := height / image originalHeight
		
		if (wr < hr) then(
			glTranslated(0, (height - (image originalHeight * wr))/2, 0)
			glScaled(wr, wr, 1)
		) else(
			glTranslated((width - (image originalWidth * hr)) / 2, 0, 0)
			glScaled(hr, hr, 1)
		)
		
	)
	
	drawProportional := method(
		glPushMatrix
		translateToPlacement
		drawColor
		glColor4d(1, 1, 1, .1)
		image drawTexture
		if(isSelected and superview isFirstResponder, drawBorder)
		glPopMatrix
		
		//glColor4d(0,0,1,.2)
		//glRectd(0, 0, width, height)
        //drawBorder
		self
	)

	newSlot("borderColor", Color clone set(1,1,1,1))
	newSlot("borderSize", 1)

    setIsClipped(false)
    
	drawBorder := method(
		glPushMatrix
        //translateToPlacement
		b := borderSize
		w := image originalWidth
		h := image originalHeight - b
		
		borderColor glColor
		glBegin(GL_LINE_LOOP)
		glVertex2d(0,0)
		glVertex2d(0,h)
		glVertex2d(w,h)
		glVertex2d(w,0)
        glEnd		
		/*
		glRecti(0, 0, w, b) // bottom
		glRecti(0, h-b, w, h) // top
		glRecti(0, b, b, h-b) // left
		glRecti(w-b, b, w, h-b) // right
		*/
		glPopMatrix
	)
	
	newSlot("isSelected", false)
	select := method(setIsSelected(true))
	unselect := method(setIsSelected(false))
	acceptsFirstResponder := false
	//setBackgroundColor(Color clone set(1, 1, 1, 1))
	
	//drawBackground := nil
)
