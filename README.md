Gabriel Alexandre Richter 587414
Pietro Pilz de Lorenzo 588009


Relatório:

Contribuição dos membros da dupla:
As implementações do trabalho foram dividas entre os intergrantes. Gabriel foi responsável pelos controles de movimentção, câmera, bezier e colisões. Pietro foi responsável pelos objetos, texturas e iluminação.


Utilização de recursos de IA:

Duas IAs foram utilizadas, ChatGPT e Gemini. Sua função manteve-se principalmente em debug e explicação de conceitos. Há códigos criados por essas IAs na parte de colisões e de iluminação. Para o restante do código, elas não foram necessárias ou não geraram um resultado satisfatório. A geração de código por elas mostrou-se limitada quanto ao macro do trabalho, não conseguindo integrar grandes trechos funcionais. Isso as restringiu a auxilios pequenos, como suavizar a transição da iluminação ou identificar quais aspectos deveriam ser utilizados em certas colisões.


Implementado:

Movimentação do modelo do T-Rex controlado pelo usuário. Teclas W,A,S e D para movimento para frente, para trás e para os lados. Esses controles mudam a aceleração do modelo na cena, que faz a velocidade variar de acordo com o tempo, existindo uma inércia no objeto.

Dois modelos de câmera foram implementados, o LookAt, uma câmera que segue a parte traseira do T-Rex, e uma first person camera, que acompanha a visão do objeto em relação a cena. O segundo modelo para a renderização do T-Rex enquanto é utilizado. Para realizar a troca entre os modelos o usuário deve usara a tecla C. O controle de ambas as câmeras é feito pelo mouse e sua posição em relação ao eixo horizontal da tela.


Há 6 modelos sendo utilizados na aplicação, cada um com suas texturas: 

"T-Rex_Model.obj": T-Rex controlado pelo usuário. Possui duas texturas compostas, uma em cores e outra em preto e branco (GRANDECO.jpg e GRANDEB2.jpg).

"MapleTree.obj": árvore apenas com tronco e galhos renderizada em posições definidas e igualmente espaçadas por meio de um loop (a aplicação utiliza de 121 árvores). Textura de tronco de árvore (maple_bark.png).

"MapleTreeLeaves.obj": folhas renderizadas junto à árvore. Textura de folha verde (folha.png).

"STEGOSRS.obj": outro dinossauro, segue curvas de bezier para orbitar inicialmente o centro e, após, árvores escolhidas de modo aleatório. Textura de estegossauro (STEGOSRS_1.png).

"plane.obj": plano renderizado como o chão sobre o qual os objetos listados ficam sobre. Utiliza uma textura de grama repetida ao longo de sua composição (GL_REPEAT) para evitar deformação da textura (grass.png).

"sphere.obj": esfera renderizada ao redor de toda a cena. Textura de céu (azul.jpg).

Modelos e texturas retirados de https://free3d.com/pt/3d-models/.

Todos os modelos e texturas encontram-se na pasta "data".

Há dois tipos de rasterização. Para o T-Rex, plano, árvores, folhas e esfera é utilizado o modelo de Blinn-Phong. Para o estegossauro é utilizado Gouraud.

Há dois tipos de iluminação. Para T-Rex, plano, árvores e folhas é utilizada a iluminação de Phong. Para a esfera é utilizada a iluminação de Lambert.

As iluminações se combinam para dividir a cena entre uma parte mais iluminada e uma mais escura.

Há três tipos de colisão implementados:

Bounding box e plano: Paredes invisíveis que impedem T-Rex de sair da cena

Bounding box e cilindro: É gerado um cilindro invisível ao redor de cada tronco de árvore para realizar a colisão do dinossauro coma a árvore.

Bounding box e bounding box: Colisão entre os dois dinossauros.

Mecanicamente, os dois primeiros tipos de colisão zeram a velocidade e acelerção do T-Rex. A colisão entre os dinossauros produz dois efeitos, o modelo do T-Rex tem seu tamanho aumentado em um valor fixo e o modelo do estegossauro muda sua posição (escolhe aleatoriamente uma árvore e passa a girar ao redor dela).


Conceitos utilizados:

Utilizar o tempo para realizar transformações: transformações e interações realizadas com base no tempo, independente da velocidade de CPU e GPU

Transformações de modelos utilizando matrizes: utilizadas para modelar e mover os obejetos e a câmera

Lógica de controle não-trivial: os controles do T-Rex e da câmera não são triviais

Interação do usuário: o usuário pode controlar o T-Rex e a câmera utilizando mouse e teclado

Utilização e transformação de modelos complexos e texturas: utilizados em todos os elementos da cena (todos são objetos com textura manipulados por transformações matriciais). Além disso, são utilizadas as bounding boxes de alguns objetos 

Controle de câmera: feito através do mouse e seguem a movimentação do T-Rex, seja na LookAt ou na first person camera

Obejto com mais de uma instância: as árvores são geradas em 121 posições diferentes simultâneamente

Testes de intersecção: três tipos utilizados

Implementação de diferentes tipos de iluminação: Phong e Lambertiana utilizadas

Implementação de diferentes tipos de rasterização: Gouraud e Blinn-Phong utilizados

Funcionamento de curvas de bezier: movimentar o estegossauro


Passos necessários para compilação e execução:

Após baixar todos os arquivos, é possível utilizar o a aplicação CodeBlocks para compilar e executar.
É possível executar por meio do arquivo main.exe em bin->debug->main.exe
