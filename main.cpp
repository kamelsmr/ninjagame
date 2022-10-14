#include <stdio.h>
#include <SDL.h>
#include <stdlib.h>
#define GRAVITY_SPEED 0.6
#define MAX_FALL_SPEED 15
#define JUMP_HEIGHT 10
#define TICK_INTERVAL    30



int main(int argc, char** argv)
{

    int i=0;
    // ************************************************
    // A EFFECTUER UNE SEULE FOIS EN DEBUT DE PROGRAMME
    // ************************************************
    // Initialisation simple
    if (SDL_Init(SDL_INIT_VIDEO) != 0 )
    {
        fprintf(stdout,"Echec de l'initialisation de la SDL (%s)\n",SDL_GetError());
        return -1;
    }

    // Creation de la fenêtre
    SDL_Window* window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_CreateWindowAndRenderer(800, 480, 0, &window, &renderer);
    if (!window || !renderer)
        return -1;
    SDL_SetRenderDrawColor(renderer, 0, 100, 0, 255); // Couleur de fond : rouge, vert, bleu, transparence



    // initialisation TTF (affichage textes)
//    TTF_Init();
//    TTF_Font* police = TTF_OpenFont("04B_30__.ttf", 24);
//    if (!police)
//        return -1;
//    SDL_Color White = {255, 255, 255};
//    SDL_Surface* message = TTF_RenderText_Solid(police, "Ninja", White);
//    SDL_Texture* tex_message = SDL_CreateTextureFromSurface(renderer, message);
//    SDL_Rect position_message;
//    position_message.x = 20;
//    position_message.y = 30;
//    position_message.w = 100;
//    position_message.h = 20;

    // Chargement d'une image et initialisation de sa position à l'écran
    SDL_Surface *image1 = SDL_LoadBMP("fond_mario.bmp");
    if (!image1)
        return -1;
    SDL_Texture *tex_image1 = SDL_CreateTextureFromSurface(renderer, image1);
    if (!tex_image1)
        return -1;
    SDL_Rect position_image1;
    //SDL_QueryTexture(tex_image1,NULL, NULL, &position_image1.w, &position_image1.h);
    position_image1.x = 0;
    position_image1.y = 0;
    position_image1.w=800;
    position_image1.h=480;

    // Chargement d'une 2e image et initialisation de sa position à l'écran
    SDL_Surface *perso1 = SDL_LoadBMP("attack_1.bmp");
    SDL_Surface *perso_att = SDL_LoadBMP("attack_2.bmp");
    SDL_Surface *ennemi = SDL_LoadBMP("run_1.bmp");
    SDL_Surface *perso1_flip = SDL_LoadBMP("attack_1_flip.bmp");
    SDL_Surface *perso_att_flip = SDL_LoadBMP("attack_2_flip.bmp");
    SDL_Surface *ennemi_flip = SDL_LoadBMP("run_1_flip.bmp");
//    SDL_Surface *ennemi2 = SDL_LoadBMP("ennemi2.bmp");
//    SDL_Surface *ennemi2_flip = SDL_LoadBMP("ennemi2_flip.bmp");
    SDL_Surface *attack_dash = SDL_LoadBMP("attack_dash.bmp");
    SDL_Surface *attack_dash_flip = SDL_LoadBMP("attack_dash_flip.bmp");
    SDL_Surface *jump0 = SDL_LoadBMP("jump0.bmp");
    SDL_Surface *jump0_flip = SDL_LoadBMP("jump0_flip.bmp");
    SDL_Surface *test = SDL_LoadBMP("test.bmp");

    SDL_SetColorKey(perso1, SDL_TRUE, SDL_MapRGB(perso1->format, 0, 255, 0)); // permet la transparence du fond de nnotrtee personnage
    SDL_SetColorKey(perso_att, SDL_TRUE, SDL_MapRGB(perso_att->format, 0, 255, 0)); // permet la transparence du fond de nnotrtee personnage
    SDL_SetColorKey(ennemi, SDL_TRUE, SDL_MapRGB(perso1->format, 0, 255, 0)); // permet la transparence du fond de nnotrtee personnage
    SDL_SetColorKey(perso1_flip, SDL_TRUE, SDL_MapRGB(perso1->format, 0, 255, 0)); // permet la transparence du fond de nnotrtee personnage
    SDL_SetColorKey(perso_att_flip, SDL_TRUE, SDL_MapRGB(perso_att->format, 0, 255, 0)); // permet la transparence du fond de nnotrtee personnage
    SDL_SetColorKey(ennemi_flip, SDL_TRUE, SDL_MapRGB(perso1->format, 0, 255, 0)); // permet la transparence du fond de nnotrtee personnage
//    SDL_SetColorKey(ennemi2, SDL_TRUE, SDL_MapRGB(perso1->format, 0, 255, 0)); // permet la transparence du fond de nnotrtee personnage
//    SDL_SetColorKey(ennemi2_flip, SDL_TRUE, SDL_MapRGB(perso1->format, 0, 255, 0)); // permet la transparence du fond de nnotrtee personnage
    SDL_SetColorKey(attack_dash, SDL_TRUE, SDL_MapRGB(perso1->format, 0, 255, 0));
    SDL_SetColorKey(attack_dash_flip, SDL_TRUE, SDL_MapRGB(perso1->format, 0, 255, 0));
    SDL_SetColorKey(jump0, SDL_TRUE, SDL_MapRGB(perso1->format, 0, 255, 0));
    SDL_SetColorKey(jump0_flip, SDL_TRUE, SDL_MapRGB(perso1->format, 0, 255, 0));
    SDL_SetColorKey(test, SDL_TRUE, SDL_MapRGB(perso1->format, 0, 255, 0));
    if (!perso1)
        return -1;
    SDL_Texture *tex_perso1 = SDL_CreateTextureFromSurface(renderer, perso1);
    if (!tex_perso1)
        return -1;
    SDL_Rect position_perso1;
    SDL_QueryTexture(tex_perso1,NULL, NULL, &position_perso1.w, &position_perso1.h);
    position_perso1.x = 200;
    position_perso1.y = 349;

    if (!jump0)
        return -1;
    SDL_Texture *tex_jump0 = SDL_CreateTextureFromSurface(renderer, jump0);
    if (!tex_jump0)
        return -1;
    SDL_Rect position_jump0;
    SDL_QueryTexture(tex_jump0,NULL, NULL, &position_jump0.w, &position_jump0.h);
    position_jump0.x =position_perso1.x;
    position_jump0.y =position_perso1.y;

    if (!ennemi)
        return -1;
    SDL_Texture *tex_ennemi = SDL_CreateTextureFromSurface(renderer, ennemi);
    if (!tex_jump0)
        return -1;
    SDL_Rect position_ennemi;
    SDL_QueryTexture(tex_ennemi,NULL, NULL, &position_ennemi.w, &position_ennemi.h);
    position_ennemi.x =600;
    position_ennemi.y =position_perso1.y;

    if (!jump0_flip)
        return -1;
    SDL_Texture *tex_jump0_flip = SDL_CreateTextureFromSurface(renderer, jump0_flip);
    if (!tex_jump0_flip)
        return -1;
    SDL_Rect position_jump0_flip;
    SDL_QueryTexture(tex_jump0_flip,NULL, NULL, &position_jump0_flip.w, &position_jump0_flip.h);
    position_jump0_flip.x = position_jump0.x;
    position_jump0_flip.y = position_jump0.y;

    if (!perso_att)
        return -1;
    SDL_Texture *tex_perso_att = SDL_CreateTextureFromSurface(renderer, perso_att);
    if (!tex_perso_att)
        return -1;
    SDL_Rect position_perso_att;
    SDL_QueryTexture(tex_perso_att,NULL, NULL, &position_perso_att.w, &position_perso_att.h);
    position_perso_att.x = position_perso1.x;
    position_perso_att.y = position_perso1.y;



    if (!test)
        return -1;
    SDL_Texture *tex_test = SDL_CreateTextureFromSurface(renderer, test);
    if (!tex_test)
        return -1;
    SDL_Rect position_test[10];

    for(i=0; i<10; i++)
    {
        SDL_QueryTexture(tex_test,NULL, NULL, &position_test[i].w, &position_test[i].h);
        position_test[i].x =rand()%800 ;
        position_test[i].y = 349;
    }


    if (!perso1_flip)
        return -1;
    SDL_Texture *tex_perso1_flip = SDL_CreateTextureFromSurface(renderer, perso1_flip);
    if (!tex_perso1_flip)
        return -1;
    SDL_Rect position_perso1_flip;
    SDL_QueryTexture(tex_perso1_flip,NULL, NULL, &position_perso1_flip.w, &position_perso1_flip.h);
    position_perso1_flip.x =  position_perso1.x;
    position_perso1_flip.y =  position_perso1.y;

    if (!perso_att_flip)
        return -1;
    SDL_Texture *tex_perso_att_flip = SDL_CreateTextureFromSurface(renderer, perso_att_flip);
    if (!tex_perso_att_flip)
        return -1;
    SDL_Rect position_perso_att_flip;
    SDL_QueryTexture(tex_perso_att,NULL, NULL, &position_perso_att_flip.w, &position_perso_att_flip.h);
    position_perso_att_flip.x = position_perso_att.x;
    position_perso_att_flip.y = position_perso_att.y;

    if (!ennemi_flip)
        return -1;
    SDL_Texture *tex_ennemi_flip = SDL_CreateTextureFromSurface(renderer, ennemi_flip);
    if (!tex_ennemi_flip)
        return -1;
    SDL_Rect position_ennemi_flip;
    for(i=0; i<10; i++)
    {
        SDL_QueryTexture(tex_ennemi_flip,NULL, NULL, &position_ennemi_flip.w, &position_ennemi_flip.h);
        position_ennemi_flip.x = position_test[i].x;
        position_ennemi_flip.y = position_test[i].y;
    }

    if (!attack_dash)
        return -1;
    SDL_Texture *tex_attack_dash = SDL_CreateTextureFromSurface(renderer, attack_dash);
    if (!tex_attack_dash)
        return -1;
    SDL_Rect position_attack_dash;
    SDL_QueryTexture(tex_attack_dash,NULL, NULL, &position_attack_dash.w, &position_attack_dash.h);
    position_attack_dash.x = position_perso1.x;
    position_attack_dash.y = position_perso1.y;



    if (!attack_dash_flip)
        return -1;
    SDL_Texture *tex_attack_dash_flip = SDL_CreateTextureFromSurface(renderer, attack_dash_flip);
    if (!tex_attack_dash_flip)
        return -1;
    SDL_Rect position_attack_dash_flip;
    SDL_QueryTexture(tex_attack_dash_flip,NULL, NULL, &position_attack_dash_flip.w, &position_attack_dash_flip.h);
    position_attack_dash_flip.x = position_attack_dash.x;
    position_attack_dash_flip.y = position_attack_dash.y;

    // On soustrait des coordonnées de notre héros, ceux du début de la map, pour qu'il colle
    //au scrolling :



    int quit = 0,u;
    int t_first = SDL_GetTicks();
    int t_down, t_int, t_attack, gauche, droite = 0;
    int jump, attack, dash, t_dash = 0;
    int mort = 0;
    int mort2 = 0;
    int t_mort = 0;
    int t_mort2 = 0;
    int viesJ = 0; //vie joueur intermédiaire
    int viesperso=3;
    int mort_test[10] ;
    int t_mort_test[10];
    int scorebis =0;

    SDL_Texture* tex_perso1_sv = tex_perso1;
    SDL_Texture* tex_perso_att_sv = tex_perso_att;
    SDL_Texture* tex_test_sv = tex_ennemi;



    for(i=0; i<10; i++)
    {
        SDL_QueryTexture(tex_test,NULL, NULL, &position_test[i].w, &position_test[i].h);
        position_test[i].x =rand()%800 ;
        position_test[i].y = 349;
    }

    for(i=0; i<10; i++)
    {
        mort_test[i]=0;
    }


    for(i=0; i<10; i++)
    {
        t_mort_test[i]=0;
    }

    int score = 0;
    while(!quit)
    {
        int player_vely = 0;
        // Déclaration des variables
        int t_now = SDL_GetTicks();

        int ground_level = 432;


        // Système de limitation des FPS
        Uint32 startTime = 0;
        Uint32 endTime = 0;
        Uint32 delta = 0;
        short fps = 60;
        short timePerFrame = 16; // miliseconds
        if (!startTime)
        {
            // get the time in ms passed from the moment the program started
            startTime = SDL_GetTicks();
        }
        else
        {
            delta = endTime - startTime; // how many ms for a frame
        }


        // if less than 16ms, delay
        if (delta < timePerFrame)
        {
            SDL_Delay(timePerFrame - delta);
        }

        // if delta is bigger than 16ms between frames, get the actual fps
        if (delta > timePerFrame)
        {
            fps = 1000 / delta;
        }

//        printf("FPS is: %i \n", fps);
//        printf("viesJ: %i vies: %i \n", viesJ,viesperso);
//        printf("vies: %i \n", viesperso);
//        printf("viesJ: %i vies: %i score:  %i \n",viesJ,viesperso, score);
        printf("sorebis =:  %i \n", scorebis);
//          printf("position perso1:  %i \n", position_perso1.y);


        startTime = endTime;
        endTime = SDL_GetTicks();
        if(viesperso==0)                  //GAME OVER
        {
            printf("game over sale merde\n\n\n\n") ;
            quit = true;
            SDL_Delay(100);
            SDL_PumpEvents();
            SDL_DestroyTexture(tex_image1);
            SDL_FreeSurface(image1);
//                    SDL_DestroyTexture(tex_message);
//                    SDL_FreeSurface(message);
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
//                    TTF_Quit();
            SDL_Quit();
            return 0;

        }


        // Affichage des sprites
        SDL_Event e;
        SDL_RenderClear(renderer);
        SDL_RenderCopy (renderer, tex_image1, NULL, &position_image1);
        SDL_RenderCopy (renderer, tex_perso1, NULL, &position_perso1);

        for(i=0; i<10; i++)
        {
            if(mort_test[i]==0)
            {
                SDL_RenderCopy (renderer, tex_test, NULL, &position_test[i]);
            }

        }



//        SDL_RenderCopy (renderer, tex_message, NULL, &position_message);
        SDL_RenderPresent (renderer);
        SDL_PollEvent(&e);

        // Système de gravité / vélocité
        if (position_perso1.y + position_perso1.h <= ground_level)
        {
            player_vely += 0.3;
        }
        else
        {
            player_vely = -player_vely / 3;
            position_perso1.y = ground_level - position_perso1.h;
        }
        position_perso1.y += player_vely;

        if(e.type == SDL_QUIT)
        {
            quit = 1;
            break;
        }
        else if(e.type == SDL_KEYDOWN && position_perso1.y == (ground_level - position_perso1.h))
        {
            switch (e.key.keysym.sym)
            {

            case SDLK_LEFT:
                droite = 0;
                gauche = 1;
                tex_perso1 = tex_perso1_flip;
                if(position_perso1.x >= -15)
                {
                    position_perso1.x -=5;
                }
                else
                {
                    position_perso1.x -= 0;
                }



                break;

            case SDLK_RIGHT:
                gauche = 0;
                if(position_perso1.x <= 730)
                {
                    position_perso1.x +=5;
                }
                else
                {
                    position_perso1.x -= 0;
                }
                droite = 1;
                tex_perso1 = tex_perso1_sv;

                break;

            case SDLK_SPACE:
                t_attack = SDL_GetTicks();
                attack = 1;
                break;

            case SDLK_UP:
                t_down = SDL_GetTicks();
                jump = 1;
                break;

            case SDLK_DOWN:
                if(scorebis>=2000)
                {
                    dash=1;
                    t_dash=SDL_GetTicks();
                }
                break;

            case SDLK_ESCAPE:
                quit = true;
                SDL_Delay(100);
                SDL_PumpEvents();
                SDL_DestroyTexture(tex_image1);
                SDL_FreeSurface(image1);
//                    SDL_DestroyTexture(tex_message);
//                    SDL_FreeSurface(message);
                SDL_DestroyRenderer(renderer);
                SDL_DestroyWindow(window);
//                    TTF_Quit();
                SDL_Quit();
                return 0;
                break;
            }


        }



        if(dash==1) //gestion du dash
        {
            scorebis=0;  // renitialisation du dash
            if(droite==1 )
            {
                tex_perso1 = tex_attack_dash;
                if(position_perso1.x <= 730)
                {
                    position_perso1.x +=20;
                }
                else
                {
                    position_perso1.x -= 0;
                }
            }
            else
            {
                tex_perso1 = tex_attack_dash_flip;
                if(position_perso1.x >= -15)
                {
                    position_perso1.x -=20;
                }
                else
                {
                    position_perso1.x -= 0;
                }
            }

            if(t_dash+200<t_now)
            {
                if(droite==1)
                {
                    tex_perso1 = tex_perso1_sv;
                    dash = 0;
                }
                else
                {
                    tex_perso1 = tex_perso1_flip;
                    dash = 0;
                }


            }

        }





        if (attack == 1)
        {
            if (gauche==1)
            {
                tex_perso1 = tex_perso_att_flip;
            }
            if(droite==1)
            {
                tex_perso1 = tex_perso_att;
            }


            if(t_attack+350<t_now)
            {
                tex_perso1 = tex_perso1_sv;
                attack = 0;

            }
        }





        // NOUVEAU CODE

        for(i=0; i<10; i++)
        {


            if (((attack == 1)&&(position_perso1.x < position_test[i].x)&&(position_perso1.x + 50 > position_test[i].x)&&(gauche==0))||((dash==1)&& (position_perso1.x < position_test[i].x)&&(gauche==0)))
            {

                mort_test[i] = 1; // ennemi mort
                score = score + 100;
                scorebis= scorebis + 100;
                position_test[i].x=rand()%800;  // changer la position de respawn de l'ennemi
                t_mort_test[i] = SDL_GetTicks();


            }

            if (((attack == 1)&&(position_perso1.x > position_test[i].x)&&(position_perso1.x - 50 < position_test[i].x)&&(droite==0))||((dash==1)&& (position_perso1.x > position_test[i].x)&&(droite==0)))
            {

                mort_test[i] = 1;
                score = score + 100;
                scorebis= scorebis + 100;
                position_test[i].x=rand()%800;  // changer la position de respawn de l'ennemi
                t_mort_test[i] = SDL_GetTicks();



            }
        }

        for(i=0; i<10; i++)
        {
            if((position_test[i].x > position_perso1.x + 35)&&(mort_test[i]==0)) //déplacement auto zombie gauche
            {

                tex_test = tex_ennemi_flip;
                position_test[i].x -= 2;

            }
            if((position_test[i].x < position_perso1.x-35)&&(mort_test[i]==0))
            {
                tex_test = tex_ennemi;
                position_test[i].x += 2;
            }

        }


        for(i=0; i<10; i++)
        {

            if((t_mort_test[i]+500<t_now)&&(mort_test[i] == 1))   // respawn  zombie
            {
                mort_test[i] = 0;
            }
        }


        //FIN NOUVEAU CODE



//
//        if (((position_perso1.x > position_ennemi.x)&&(position_perso1.x  < position_ennemi.x + 40))&&(position_perso1.y>340)&& (mort == 0)) //syteme perte de vie
//        {
//
//            viesJ--;
//        }
//
//        if (((position_perso1.x < position_ennemi.x)&&(position_perso1.x  > position_ennemi.x - 40))&&(position_perso1.y>340)&& (mort == 0)) //syteme perte de vie
//        {
//
//            viesJ--;
//        }
//
//


        if((viesJ < -100))  //perte de vie du joueur
        {
            viesperso--;
            viesJ=0;
        }




        if (jump == 1)
        {



            if ( t_down <= t_now ) //  if ( t_down + 1500 > t_now )
            {
                position_perso1.y -= 6;
            }


            t_int = SDL_GetTicks(); //inutile car il est pris continuellement tant que jump == 1 donc tout le temps


            if ( t_now  >= t_down + 275 &&  position_perso1.y <= 345 )
            {
                position_perso1.y += 10;
            }


//
//            if ( t_int  <= t_down + 250 ) // ancien saut
//          {
//                position_perso1.y += 10;
//            }
//                                            //(position_perso1.y == ((ground_level - position_perso1.h)+1))

            if (position_perso1.y < 345)  //déplacement lors du saut
            {
                if(gauche == 1) //jump = 0;
                {
                    tex_perso1 = tex_jump0_flip;

                    if(position_perso1.x >= -15)
                    {
                        position_perso1.x -=5;
                    }
                    else
                    {
                        position_perso1.x -= 0;
                    }

                }
                if(droite == 1)
                {
                    tex_perso1 = tex_jump0;
                    if(position_perso1.x <= 730)
                    {
                        position_perso1.x +=5;
                    }
                    else
                    {
                        position_perso1.x -= 0;
                    }
                }


            }
//         if (position_perso1.y > 345)                    //remettre le bon sprite après le saut
//         {
//            if (gauche == 0) {
//             tex_perso1 = tex_perso1_sv; }
//             else { tex_perso1 = tex_perso1_flip; }
//         }


        }
    }
}



