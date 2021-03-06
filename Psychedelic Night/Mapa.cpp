/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Mapa.h"

using namespace std;



Mapa::Mapa() {
     _numLayers=0;
     _numObject=0;
     activeLayer=0;
   
}

Mapa::Mapa(const Mapa& orig) {
}

Mapa::~Mapa() {
    for(int l=0; l<_numLayers; l++){
        for(int y=0; y<_height; y++){
            delete[] _tilemap[l][y];
        }
        delete[] _tilemap[l];
    }
    delete[] _tilemap;
    for(int t=0; t<NHAB; t++){
        for(int l=0; l<_numLayers; l++){
            for(int y=0; y<_height; y++){
                delete[] _tilemapSprite[t][l][y];
                delete[] _tiles[t][l][y];
            }
            delete[] _tilemapSprite[t][l];
            delete[] _tiles[t][l];
        }
        delete _tilemapSprite[t];
        delete[] _tiles[t];
    } 
    delete[] _tilemapSprite;
    delete[] _tiles;
    delete[] _tilesetSprite;
    delete[] _tilesetSpriteobj;       
}

void Mapa::leerMapa(int NH){
    NHAB = NH;
    //creo el objeto xml
    TiXmlDocument doc;
    doc.LoadFile("muros.tmx");
    TiXmlElement* map = doc.FirstChildElement("map");
    
    if (!roca.loadFromFile("resources/roca.png")){
        std::cerr << "Error cargando las texturas";
        exit(0);
    }
    if (!fuego.loadFromFile("resources/mierda.png")){
        std::cerr << "Error cargando las texturas";
        exit(0);
    }
    if (!pinchos.loadFromFile("resources/pinchos.png")){
        std::cerr << "Error cargando las texturas";
        exit(0);
    }

    //leo sus atributos
    map->QueryIntAttribute("width",&_width);
    map->QueryIntAttribute("height",&_height);
    map->QueryIntAttribute("tilewidth",&_tileWidth);
    map->QueryIntAttribute("tileheight",&_tileHeigth);
    
    //Leemos las diferentes imagenes que nos sirven para hacer el rect de las texturas
    TiXmlElement *img = map->FirstChildElement("tileset");
    int numTil=0;
    while(img){
        numTil++;
        img=img->NextSiblingElement("tileset");
    }
    
    string filename;

    img = map->FirstChildElement("tileset");
    //guardamos en filename el spritesheet
    while(img){
        filename=(string)img->FirstChildElement("image")->Attribute("source");
        img=img->NextSiblingElement("tileset");
    }  
    //leemos las diferentes capas
    _tilesetTexture.loadFromFile(filename);
    TiXmlElement *layer = map->FirstChildElement("layer");
    while(layer){
        _numLayers++;
        layer= layer->NextSiblingElement("layer");
    }  
    //nopeta
    //Reserva de memoria para saber el numnero de capas y el tamaño 
    _tilemap=new int**[_numLayers];
    for(int i=0; i<_numLayers; i++){
        _tilemap[i]=new int*[_height];
    }
   
    for(int l=0; l<_numLayers; l++){
        for(int y=0; y<_height; y++){
            _tilemap[l][y]=new int[_width];
        }
    }

    TiXmlElement *data;
    //leemos el atributo imagen
    layer = map->FirstChildElement("layer");
    string *name=new string[_numLayers];
    int j=0;
    int l=0;
    //leo los tiles del xml y avanzo a la siguiente posicion
    while(layer){
        data= layer->FirstChildElement("data")->FirstChildElement("tile");
        name[j]= (string)layer->Attribute("name");
            while(data){
                for(int y=0; y<_height; y++){
                    for(int x=0; x<_width;x++){
                        data->QueryIntAttribute("gid",&_tilemap[l][y][x]);
                        data=data->NextSiblingElement("tile");
                    }
                }
            }
        l++;
        layer= layer->NextSiblingElement("layer");
        j++;
    } 
    //Reserva de memoria para los sprites
    _tilemapSprite=new sf::Sprite****[NH];
    _tiles=new int***[NH];
    for(int t=0; t<NH; t++){
        _tilemapSprite[t] = new sf::Sprite***[_numLayers];
        _tiles[t]=new int**[_numLayers];
    for(int l=0; l<_numLayers; l++){
        _tilemapSprite[t][l]=new sf::Sprite**[_height];
        _tiles[t][l]=new int*[_height];
    }
    } 
    for(int t=0; t<NH; t++){
    for(int l=0; l<_numLayers; l++){
        for(int y=0; y<_height; y++){
            _tilemapSprite[t][l][y]= new sf::Sprite*[_width];
            _tiles[t][l][y]=new int[_width];
            for(int x=0; x<_width; x++){
                _tilemapSprite[t][l][y][x]=new sf::Sprite();
                _tiles[t][l][y][x]=0;
            }
        }
    }
    }
    
    //falta el corte
    
    int columns = _tilesetTexture.getSize().x / _tileWidth;
    int rows = _tilesetTexture.getSize().y / _tileHeigth;
    


    _tilesetSprite =new sf::Sprite[columns*rows]; 
    _tilesetSpriteobj =new sf::Sprite[columns*rows]; 

    int t=0;
    for(int y=0; y<rows; y++){
        for(int x=0; x<columns;x++){
              _tilesetSprite[t].setTexture(_tilesetTexture);
              //_tilesetSprite[t].setTextureRect(sf::IntRect(left,top,width,height));//ojo si hay dos imagenes
              _tilesetSprite[t].setTextureRect(sf::IntRect(x*_tileWidth,y*_tileHeigth,_tileWidth,_tileHeigth));
              t++;
        }
    }
    
}

void Mapa::setPosition(int puer[], int h, int ancho, int alto) {
    int r1 = (int) 50 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(200)));
    int r2 = (int) 50 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(200)));
    int r3 = (int) 50 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(200)));
    int cont = 0;
    while(cont < 15){
        int x = 0 + rand()%(39-4);
        int y = 0 + rand()%(23-4);
        if( x==18 || x ==19 || x==20 || x==21 ){
            x = 16;
        }
        if( y==10 || y==11 || y==12 || y==13){
            y=15;
        }
        if(_tilemap[1][y][x] == 0){
            _tilemap[1][y][x] = 2 + rand()%(4-1);
            
            cont = cont + 1;
            if(_tilemap[1][y][x] == 2){
                _tilemapSprite[h][1][y][x]= new sf::Sprite(fuego);
                _tiles[h][1][y][x]=1;
                _tiles[h][1][y-1][x]=1;
                _tiles[h][1][y-1][x+1]=1;
                _tiles[h][1][y][x+1]=1;
                
            }
            else if(_tilemap[1][y][x] == 3){
                _tilemapSprite[h][1][y][x]=new sf::Sprite(roca);
                _tiles[h][1][y][x]=1;
                _tiles[h][1][y-1][x]=1;
                _tiles[h][1][y-1][x+1]=1;
                _tiles[h][1][y][x+1]=1;
            }          
        }
    }
    
    int columns = _tilesetTexture.getSize().x / _tileWidth;
    int rows = _tilesetTexture.getSize().y / _tileHeigth;
    
    for(int l=0; l<2; l++){
        for(int y=0; y<_height; y++){
            for(int x=0; x<_width;x++){
                int gid=_tilemap[l][y][x]-1;
                if(gid>=rows*columns){ }
                else if(gid>0){   
                    if(gid == 1 || gid==2 || gid==3){
                        _tilemap[1][y][x]=0;
                        
                       _tilemapSprite[h][1][y][x]->setPosition(x*_tileWidth+(ancho*(20*_width)),y*_tileHeigth+(alto*(20*_height)));

                    }
                    else {
                    _tilemapSprite[h][l][y][x]=new sf::Sprite(_tilesetTexture,_tilesetSprite[gid].getTextureRect());
                    _tilemapSprite[h][l][y][x]->setColor(sf::Color(r1, r2, r3));
                    _tilemapSprite[h][l][y][x]->setPosition(x*_tileWidth+(ancho*(20*_width)),y*_tileHeigth+(alto*(20*_height)));
                    _tiles[h][l][y][x]=1;
                    }
                }
                else{
                    _tilemapSprite[h][l][y][x]=NULL;
                }
            }
        }
    }
    for(int l=2; l<_numLayers; l++){
            for(int y=0; y<_height; y++){
                for(int x=0; x<_width;x++){
                    int gid=_tilemap[l][y][x]-1;
                    if(gid>=rows*columns){ }
                    else if(gid>0 && puer[l-2]==1){ 
                        _tilemapSprite[h][l][y][x]=new sf::Sprite(_tilesetTexture,_tilesetSprite[gid].getTextureRect());
                        _tilemapSprite[h][l][y][x]->setColor(sf::Color(r1, r2, r3));
                        _tilemapSprite[h][l][y][x]->setPosition(x*_tileWidth+(ancho*(20*_width)),y*_tileHeigth+(alto*(20*_height)));
                    }
                    else{
                        _tilemapSprite[h][l][y][x]=NULL;
                    }
                }
            }
        }
      
        for(int l=2; l<_numLayers; l++){
            for(int y=0; y<_height; y++){
                        for(int x=0; x<_width;x++){
                            if((_tilemap[l][y][x]-1)>0 && puer[l-2]==1){
                                _tiles[h][l][y][x]=1;
                            }
                        }
                    }        
        }
}
/*
    bool mapa::devolverColision(int posX, int posY){
        bool devol = false;
        if( _tilemap[1][posY/15][posX/25] != 0){
            devol=true;
        }
        return devol;
    }
*/

void Mapa::dibuja(int habs){
    Motor2D*motor2D = Motor2D::Instance();

    int t=0, h=0;
    while(h<habs){
        while(t<6){
            for(int y=0; y<_height; y++){
                for(int x=0; x<_width; x++){
                    if(_tilemapSprite[h][t][y][x]!=NULL){
                        motor2D->pintarSprites(*(_tilemapSprite[h][t][y][x]));
                        //window->draw(*(_tilemapSprite[h][t][y][x]));
                    }
                }
            }
            t++;
        }
        t=0;
        h++;
    }    
}

int Mapa::getWidth(){
    return _tileWidth*_width;
}

int Mapa::getHeight(){
    return _tileHeigth*_height;
}

int Mapa::getAnchoT(){
    return _width;
}

int Mapa::getAltoT(){
    return _height;
}