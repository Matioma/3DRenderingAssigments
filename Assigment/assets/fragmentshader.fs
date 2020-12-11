#version 330

in vec3 fColor;
out vec4 sColor;

in vec2 fuv;

uniform ivec2 colsRows; 

void main (void) {

	float columns =colsRows.x;
	float rows =colsRows.y;
	
	float columnWidth = (1/columns);
	float rowHeight = (1/rows);


	float indexX = floor(fuv.x/columnWidth);
	float indexY = floor(fuv.y/rowHeight);
	
	if(mod(indexX + indexY,2.0) ==0){
		sColor = vec4(1,1,1,1);
	}else{
		sColor = vec4(0,0,0,1);
	}
}

