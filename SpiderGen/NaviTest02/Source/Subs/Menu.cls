
/**
Constructor
Do not call Function in Constructor.
*/
class Menu()
{
	super();

	//TODO:edit here

}
extends AView;


function Menu*init(context, evtListener)
{
	super.init(context, evtListener);

	//TODO:edit here

};

function Menu*onInitDone()
{
	super.onInitDone();

	//TODO:edit here

};

function Menu*onActiveDone(isFirst)
{
	super.onActiveDone(isFirst);

	//TODO:edit here

};

function Menu*onGoBtnClick(comp, info, e)
{
	theApp.navi.goPage("Page000"+comp.compId);
};
