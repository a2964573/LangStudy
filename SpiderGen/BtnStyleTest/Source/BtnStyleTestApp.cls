import "Framework/afc/component/AButton.js";

/**
Constructor
Do not call Function in Constructor.
*/
class BtnStyleTestApp()
{
	super();

	//TODO:edit here

}
extends AApplication;


function BtnStyleTestApp*onReady()
{
	super.onReady();

	this.setMainContainer(new APage('main'));
	this.mainContainer.open('Source/MainView.lay');

	//TODO:edit here

};

function BtnStyleTestApp*unitTest(unitUrl)
{
	//TODO:edit here

	this.onReady();

	super.unitTest(unitUrl);
};
