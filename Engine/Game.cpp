/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"
#include "Star.h"


Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	ct( gfx ),
	cam( ct ),
	camCtrl( wnd.mouse,cam )
{
	//entities.emplace_back( Star::Make( 100.0f,50.0f ),Vec2{ 460.0f,0.0f } );
	//entities.emplace_back( Star::Make( 150.0f,50.0f ),Vec2{ 150.0f,300.0f } );
	//entities.emplace_back( Star::Make( 100.0f,50.0f ),Vec2{ 250.0f,-200.0f } );
	//entities.emplace_back( Star::Make( 150.0f,50.0f ),Vec2{ -250.0f,200.0f } );
	//entities.emplace_back( Star::Make( 150.0f,50.0f ),Vec2{ 0.0f,0.0f } );
	//entities.emplace_back( Star::Make( 200.0f,50.0f ),Vec2{ -150.0f,-300.0f } );
	//entities.emplace_back( Star::Make( 100.0f,50.0f ),Vec2{ 400.0f,300.0f } );

	

	for (int i = 0; i < 300; i++)
	{
		int outer = r.CreateInt(50, 250);
		int inner = r.CreateInt(40, 80);
		int posX = r.CreateInt(-7500, 7500);
		int posY = r.CreateInt(-5000, 5000);
		int flares = r.CreateInt(4, 7);
		Vec2 pos = { (float)posX, (float)posY };
		Color c = { (unsigned char)r.CreateInt(0, 255),(unsigned char)r.CreateInt(0, 255),(unsigned char)r.CreateInt(0, 255) };

		while (std::any_of(entities.begin(), entities.end(), [&](Entity& e)
		{
			Vec2 temp = { pos - e.GetPos() };
			float dist = temp.Len();
			return dist <= 500.0f;
		}))
		{
			posX = r.CreateInt(-7500, 7500);
			posY = r.CreateInt(-5000, 5000);
			pos = { (float)posX, (float)posY };
		}

		entities.emplace_back(Star::Make((float)outer, (float)inner, flares), pos, c );
	}
}

void Game::Go()
{

	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	camCtrl.Update();
	
}

void Game::ComposeFrame()
{
	for( const auto& entity : entities )
	{
		
		cam.Draw(entity.GetDrawable());
	}
}
