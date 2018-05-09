
# include "my_viewer.h"
#include "MarchingCubes.h"


# include <sigogl/ui_button.h>
# include <sigogl/ui_radio_button.h>
# include <sig/sn_primitive.h>
# include <sig/sn_transform.h>
# include <sig/sn_manipulator.h>

# include <sigogl/ws_run.h>
# include <vector>

template <typename T>
using ThreeD = std::vector<std::vector<std::vector<T>>>;
std::vector<GsVec> spherePosition = vector<GsVec>(2);
std::vector<GsVec> sphereVelocity = vector<GsVec>(2);

MyViewer::MyViewer ( int x, int y, int w, int h, const char* l ) : WsViewer(x,y,w,h,l)
{
	_nbut=0;
	_animating=false;
	spherePosition[0] = (GsVec(gs_random(-2, 2), gs_random(-2, 2), gs_random(-2, 2)));
	spherePosition[1] = (GsVec(gs_random(-2, 2), gs_random(-2, 2), gs_random(-2, 2)));

	sphereVelocity[0] = (GsVec(0.1f * gs_random(-5, 5), 0.1f *gs_random(-5, 5), 0.1f * gs_random(-5, 5)));
	sphereVelocity[1] = (GsVec(0.1f *gs_random(-5, 5), 0.1f * gs_random(-5, 5), 0.1f * gs_random(-5, 5)));

	build_ui ();
	build_scene ();
}

void MyViewer::build_ui ()
{
	UiPanel *p, *sp;
	UiManager* uim = WsWindow::uim();
	p = uim->add_panel ( "", UiPanel::HorizLeft );
	p->add ( new UiButton ( "View", sp=new UiPanel() ) );
	{	UiPanel* p=sp;
		p->add ( _nbut=new UiCheckButton ( "Normals", EvNormals ) ); 
	}
	p->add ( new UiButton ( "Animate", EvAnimate ) );
	p->add ( new UiButton ( "Exit", EvExit ) ); p->top()->separate();
}

void MyViewer::add_model ( SnShape* s, GsVec p )
{
	SnManipulator* manip = new SnManipulator;
	GsMat m;
	m.translation ( p );
	manip->initial_mat ( m );

	SnGroup* g = new SnGroup;
	SnLines* l = new SnLines;
	l->color(GsColor::orange);
	g->add(s);
	g->add(l);
	manip->child(g);

	rootg()->add(manip);
}

void generateFaces(Cube cube, GsModel * m)
{

	while (!m->V.empty())
	{
		m->V.pop();
	}


	while (!m->F.empty())
	{
		m->F.pop();
	}

	GsModel::Face f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12;
	for (int i = 0; i < 8; i++)
	{
		m->V.push(cube.corners[i].point);
	}

	f1.set(0, 3, 7);	//back face 1
	f2.set(0, 7, 4);	//back face 2
	f3.set(0, 1, 2);	//left face 1
	f4.set(0, 2, 3);	//left face 2
	f5.set(1, 5, 6);	//front face 1
	f6.set(1, 6, 2);	//front face 2
	f7.set(5, 4, 7);	//right face 1
	f8.set(5, 7, 6);	//right face 2
	f9.set(2, 6, 7);	//top face 1
	f10.set(2, 7, 3);	//top face 2
	f11.set(0, 4, 5);	//bottom face 1
	f12.set(0, 5, 1);	//bottom face 2

	m->F.push(f1);
	m->F.push(f2);
	m->F.push(f3);
	m->F.push(f4);
	m->F.push(f5);
	m->F.push(f6);
	m->F.push(f7);
	m->F.push(f8);
	m->F.push(f9);
	m->F.push(f10);
	m->F.push(f11);
	m->F.push(f12);

}

void checkBoundary(GsVec center, GsVec velocity, int radius, int canvasSize) {

	if (center.x + radius > canvasSize / 2 || center.x + radius < (canvasSize * -1) / 2)
		velocity.x = velocity.x * -1;
	else if (center.y + radius > canvasSize / 2 || center.y + radius < (canvasSize * -1) / 2)
		velocity.y = velocity.y * -1;
	else if (center.x + radius > canvasSize / 2 || center.x + radius < (canvasSize * -1) / 2)
		velocity.z = velocity.z * -1;
}

SnPrimitive *sphereA, *sphereB;

float influenceFromSources(GsPnt location) {
	float influence = 0;
	return 0;
	//sphereA->
}


void MyViewer::build_scene ()
{
	int resolution = 3;

	ThreeD<GsModel*> gridOfCubes = ThreeD<GsModel*>(resolution, vector<vector<GsModel*>>(resolution, vector<GsModel*>(resolution)));
	ThreeD<SnGroup*> snGroups = ThreeD<SnGroup*>(resolution, vector<vector<SnGroup*>>(resolution, vector<SnGroup*>(resolution)));
	
	MarchingCubes march = MarchingCubes();
/*
	//retrieve grid points and store in ThreeD vec
	march.gridPoints = march.generateGrid(resolution);
	march.gridCubes = march.generateCubes(march.gridPoints, resolution);
	
	
	
	for (int i = 0; i < resolution; i++)
	{
		for (int j = 0; j < resolution; j++)
		{
			for (int k = 0; k < resolution; k++)
			{
				GsModel* m = new GsModel;
				
				generateFaces(march.gridCubes[i][j][k], m);
				gridOfCubes[i][j][k] = m;
			}
		}
	}
	
	for (int i = 0; i < resolution; i++)
	{
		for (int j = 0; j < resolution; j++)
		{
			for (int k = 0; k < resolution; k++)
			{
				snGroups[i][j][k] = new SnGroup;
				snGroups[i][j][k]->separator(true);
				snGroups[i][j][k]->add(new SnModel(gridOfCubes.at(i).at(j).at(k)));
				snGroups[i][j][k]->top<SnModel>()->color(GsColor::blue);
				rootg()->add(snGroups[i][j][k]);
				
			}
		}
	}
	*/
	sphereA = new SnPrimitive(GsPrimitive::Sphere, 0.5);
	sphereA->prim().material.diffuse = GsColor::red;
	add_model(sphereA, spherePosition[0]);

	sphereB = new SnPrimitive(GsPrimitive::Sphere, 0.5);
	sphereB->prim().material.diffuse = GsColor::red;
	add_model(sphereB, spherePosition[1]);
}

// Below is an example of how to control the main loop of an animation:
void MyViewer::run_animation ()
{
	
}

void MyViewer::show_normals ( bool b )
{
	// Note that primitives are only converted to meshes in GsModel
	// at the first draw call.
	GsArray<GsVec> fn;
	SnGroup* r = (SnGroup*)root();
	for ( int k=0; k<r->size(); k++ )
	{	SnManipulator* manip = r->get<SnManipulator>(k);
		SnShape* s = manip->child<SnGroup>()->get<SnShape>(0);
		SnLines* l = manip->child<SnGroup>()->get<SnLines>(1);
		if ( !b ) { l->visible(false); continue; }
		l->visible ( true );
		if ( !l->empty() ) continue; // build only once
		l->init();
		if ( s->instance_name()==SnPrimitive::class_name )
		{	GsModel& m = *((SnModel*)s)->model();
			m.get_normals_per_face ( fn );
			const GsVec* n = fn.pt();
			float f = 0.33f;
			for ( int i=0; i<m.F.size(); i++ )
			{	const GsVec& a=m.V[m.F[i].a]; l->push ( a, a+(*n++)*f );
				const GsVec& b=m.V[m.F[i].b]; l->push ( b, b+(*n++)*f );
				const GsVec& c=m.V[m.F[i].c]; l->push ( c, c+(*n++)*f );
			}
		}  
	}
}

int MyViewer::handle_keyboard ( const GsEvent &e )
{
	int ret = WsViewer::handle_keyboard ( e ); // 1st let system check events
	if ( ret ) return ret;

	switch ( e.key )
	{	case GsEvent::KeyEsc : gs_exit(); return 1;
		//case 'n' : { bool b=!_nbut->value(); _nbut->value(b); show_normals(b); return 1; }
		default: gsout<<"Key pressed: "<<e.key<<gsnl;
	}

	return 0;
}

int MyViewer::uievent ( int e )
{
	switch ( e )
	{	//case EvNormals: show_normals(_nbut->value()); return 1;
		case EvAnimate: run_animation(); return 1;
		case EvExit: gs_exit();
	}
	return WsViewer::uievent(e);
}
