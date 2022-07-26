
import matplotlib.pyplot as pp
import numpy as np

class DatosPerceptron:
    
    def __init__(self):
        print('Inicializa....')
        
    
    
    def ecuacion(self, x):
        y = -2.34*x+1.43
        return y
    
    
    def ecuacion2(self, x):
        y = 1.5*x-1.075
        return y    
    
    
    def plot_base(self):
        xA = [1.3, 2.3]
        yA = [0.7, 1.13]
        xB = [1.7, 2.7]
        yB = [3.3, 1.79]
        
        x = np.arange(-3.0, 3.0, 0.1)
        y = self.ecuacion(x)
        y2 = self.ecuacion2(x)
        
        pp.plot(xA, yA, 'ro')
        pp.plot(xB, yB, 'bo')
        
        pp.plot(x,y,color='green', lw=1.3)
        pp.plot(x,y2,color='gold', lw=1.3)
        
        pp.grid()
        
        pp.savefig('Figura1.png', dpi=300)
        
        pp.show()
        
        
if __name__=="__main__":
    datos = DatosPerceptron()
    datos.plot_base()
