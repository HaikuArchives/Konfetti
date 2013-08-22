#include <ScreenSaver.h>
#include <StringView.h>

#include <math.h>
#include <stdlib.h>

class Konfetti : public BScreenSaver
{
public:
	Konfetti( BMessage *archive, image_id image );
	
	void StartConfig( BView *view );
	status_t StartSaver( BView *view, bool preview );
	void Draw( BView *view, int32 frame );

};

extern "C" _EXPORT BScreenSaver *instantiate_screen_saver(BMessage *msg, image_id id)
{
	return new Konfetti(msg, id);
}

inline float rnd( float min, float max) {
	return (float)rand() / RAND_MAX * (max - min) + min;
}

Konfetti::Konfetti( BMessage *archive, image_id image )
	: 	BScreenSaver( archive, image )
{
}

void Konfetti::StartConfig( BView *view )
{
	BStringView	*stringview;
	stringview = new BStringView( BRect( 10, 10, 200, 30 ), B_EMPTY_STRING, "Konfetti" );
	stringview->SetFont( be_bold_font );
	view->AddChild( stringview );

	stringview = new BStringView( BRect( 10, 30, 200, 50 ), B_EMPTY_STRING, "Copyright ©2001 by Werner Freytag");
	view->AddChild( stringview );

	stringview = new BStringView( BRect( 10, 60, 200, 75 ), B_EMPTY_STRING, "E-Mail: freytag@gmx.de");
	view->AddChild( stringview );

	stringview = new BStringView( BRect( 10, 75, 200, 90 ), B_EMPTY_STRING, "Homepage: http://www.pecora.de/");
	view->AddChild( stringview );
}

status_t Konfetti::StartSaver( BView *view, bool preview )
{
	SetTickSize(5000);
	return B_OK;
}

void Konfetti::Draw( BView *view, int32 frame )
{

	if ( frame == 0 ) {
		view->SetDrawingMode( B_OP_ALPHA );
	}
	
	view->SetHighColor( rand() % 256, rand() % 256, rand() % 256, rnd( 50, 100 ) );

	BPoint where( rnd( 0, view->Bounds().Width() ), rnd( 0, view->Bounds().Height() ) );
	float radius = view->Bounds().Height() / 60 * rnd( 0.7, 1.5 );
	view->FillEllipse( where, radius, radius );

}
