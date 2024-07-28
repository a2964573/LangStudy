
/**
Constructor
Do not call Function in Constructor.
*/
class Page0002()
{
	super();

	//TODO:edit here

}
extends AView;


function Page0002*init(context, evtListener)
{
	super.init(context, evtListener);

	//TODO:edit here

};

function Page0002*onInitDone()
{
	super.onInitDone();

	//TODO:edit here

};

function Page0002*onActiveDone(isFirst)
{
	super.onActiveDone(isFirst);

	//TODO:edit here

};

function Page0002*onGoBtnClick(comp, info, e)
{
	var pageNum = comp.compId.slice(-1);
	
	theApp.navi.goPage("Page000"+pageNum, {});
};
