/*  Calculator used to show the correct calculations of BML math library's functions */

#include <BML\BML.h>
#include <iostream>

#ifndef PI
#define PI 3.14159265f
#endif

int main()
{
  while (true)
  {
    char pick;
    std::cout << "Enter what you want to compute with: " << std::endl;
    std::cout << "'1': 2D Vectors" << std::endl;
    std::cout << "'2': 3D Vectors" << std::endl;
    std::cout << "'3': 4D (Homogenous)Vectors" << std::endl;
    std::cout << "'4': Matrices(4x4)" << std::endl;
    std::cout << "'5': Quaternions" << std::endl;
    std::cin >> pick;
    switch (pick)
    {
    case '1':
    {
      float x, y;
      std::cout << "enter x and y values for the vector: " << std::endl;
      std::cin >> x >> y;
      BML::Vector2D v1(x, y);
      std::cout << v1 << std::endl;
      std::cout << "What do you want to do with this vector ?" << std::endl;
      char choice;
      std::cout << "Options: " << std::endl;
      std::cout << "'+': Compute addition" << std::endl;
      std::cout << "'-': Compute subtraction" << std::endl;
      std::cout << "'*': Compute multiplication" << std::endl;
      std::cout << "'/': Compute division" << std::endl;
      std::cout << "'1': Compute rotation" << std::endl;
      std::cout << "'2': Get Magnitude" << std::endl;
      std::cout << "'3': Normalize it" << std::endl;
      std::cout << "'4': Compute dot product" << std::endl;
      std::cout << "'5': Get angle between this and other vector" << std::endl;
      std::cout << "'6': Compute Lerp" << std::endl;
      std::cout << "'7': Get distance between this and other vector" << std::endl;
      std::cin >> choice;
      switch (choice)
      {
      case '+':
      {
        std::cout << "You picked addition ! Now, Enter a second vector:" << std::endl;
        std::cin >> x >> y;
        BML::Vector2D v2(x, y);
        BML::Vector2D result = v1 + v2;
        std::cout << "result: " << result << std::endl;
        break;
      }
      case '-':
      {
        std::cout << "You picked subtraction ! Now, Enter a second vector:" << std::endl;
        std::cin >> x >> y;
        BML::Vector2D v2(x, y);
        BML::Vector2D result = v1 - v2;
        std::cout << "result: " << result << std::endl;
        break;
      }
      case '*':
      {
        float scalar;
        std::cout << "You picked multiplication ! Now, Enter a scalar to multiply with:" << std::endl;
        std::cin >> scalar;
        BML::Vector2D result = v1 * scalar;
        std::cout << "result: " << result << std::endl;
        break;
      }
      case '/':
      {
        float scalar;
        std::cout << "You picked division ! Now, Enter a scalar to divide with:" << std::endl;
        std::cin >> scalar;
        BML::Vector2D result = v1 / scalar;
        std::cout << "result: " << result << std::endl;
        break;
      }
      case '1':
      {
        float angle = 0.0f;
        std::cout << "You picked rotation ! Now, Enter your required angle of rotation (in degrees):" << std::endl;
        std::cin >> angle;
        BML::Vector2D result = v1.Rotate(angle);
        std::cout << "result: " << result << std::endl;
        break;
      }
      case '2':
      {
        std::cout << "You picked get magnitude :" << std::endl;

        std::cout << "magnitude: " << v1.GetMagnitude() << std::endl;
        break;
      }
      case '3':
      {
        std::cout << "You picked normalize it :" << std::endl;
        v1.Normalize();
        std::cout << "Normalized: " << v1 << std::endl;
        break;
      }
      case '4':
      {
        std::cout << "You picked dot product computation ! Now, Enter a second vector:" << std::endl;
        std::cin >> x >> y;
        BML::Vector2D v2(x, y);
        float result = BML::StaticFunctions::Dot(v1, v2);
        std::cout << "result: " << result << std::endl;
        break;
      }
      case '5':
      {
        std::cout << "You picked angle between 2 vectors ! Now, Enter a second vector:" << std::endl;
        std::cin >> x >> y;
        BML::Vector2D v2(x, y);
        float result = BML::StaticFunctions::Angle(v1, v2);
        std::cout << "result (in radians): " << result << std::endl;
        std::cout << "result (in degrees): " << result * 180.0f / PI << std::endl;
        break;
      }
      case '6':
      {
        std::cout << "You picked lerp computation ! Now, Enter a second vector to lerp to:" << std::endl;
        std::cin >> x >> y;
        BML::Vector2D v2(x, y);
        float percent = 0.0f;
        std::cout << "Enter the speed of the lerp (0 to 1) " << std::endl;
        std::cin >> percent;
        std::cout << v1 << std::endl;
        while (v1 != v2)
        {
          v1 = BML::StaticFunctions::Lerp(v1, v2, percent);
          std::cout << v1 << std::endl;
        }
        break;
      }
      case '7':
      {
        std::cout << "You picked distance between 2 vectors ! Now, Enter a second vector:" << std::endl;
        std::cin >> x >> y;
        BML::Vector2D v2(x, y);
        float result = BML::StaticFunctions::Distance(v1, v2);
        std::cout << "distance: " << result << std::endl;
        break;
      }
      default:
        std::cin.clear();
        std::cin.ignore(INT_MAX, '\n');
        break;
      }
      system("Pause");
      system("CLS");
      break;
    }
    case '2':
    {
      float x, y, z;
      std::cout << "enter x, y and z values for the vector: " << std::endl;
      std::cin >> x >> y >> z;
      BML::Vector3D v1(x, y, z);
      std::cout << v1 << std::endl;
      std::cout << "What do you want to do with this vector ?" << std::endl;
      char choice;
      std::cout << "Options: " << std::endl;
      std::cout << "'+': Compute addition" << std::endl;
      std::cout << "'-': Compute subtraction" << std::endl;
      std::cout << "'*': Compute multiplication" << std::endl;
      std::cout << "'/': Compute division" << std::endl;
      std::cout << "'1': Compute rotation" << std::endl;
      std::cout << "'2': Get Magnitude" << std::endl;
      std::cout << "'3': Normalize it" << std::endl;
      std::cout << "'4': Compute dot product" << std::endl;
      std::cout << "'5': Get angle between this and other vector" << std::endl;
      std::cout << "'6': Compute Lerp" << std::endl;
      std::cout << "'7': Get distance between this and other vector" << std::endl;
      std::cout << "'8': Compute cross product" << std::endl;
      std::cout << "'9': Compute vector reflect" << std::endl;

      std::cin >> choice;
      switch (choice)
      {
      case '+':
      {
        std::cout << "You picked addition ! Now, Enter a second vector:" << std::endl;
        std::cin >> x >> y >> z;
        BML::Vector3D v2(x, y, z);
        BML::Vector3D result = v1 + v2;
        std::cout << "result: " << result << std::endl;
        break;
      }
      case '-':
      {
        std::cout << "You picked subtraction ! Now, Enter a second vector:" << std::endl;
        std::cin >> x >> y >> z;
        BML::Vector3D v2(x, y, z);
        BML::Vector3D result = v1 - v2;
        std::cout << "result: " << result << std::endl;
        break;
      }
      case '*':
      {
        float scalar;
        std::cout << "You picked multiplication ! Now, Enter a scalar to multiply with:" << std::endl;
        std::cin >> scalar;
        BML::Vector3D result = v1 * scalar;
        std::cout << "result: " << result << std::endl;
        break;
      }
      case '/':
      {
        float scalar;
        std::cout << "You picked division ! Now, Enter a scalar to divide with:" << std::endl;
        std::cin >> scalar;
        BML::Vector3D result = v1 / scalar;
        std::cout << "result: " << result << std::endl;
        break;
      }
      case '1':
      {
        float angle = 0.0f;
        std::cout << "You picked rotation ! Now, Enter your required angle of rotation (in degrees):" << std::endl;
        std::cin >> angle;
        char axisPick;
        std::cout << "About which axis do you want to rotate ?" << std::endl;
        std::cout << "'1': About X axis" << std::endl;
        std::cout << "'2': About Y axis" << std::endl;
        std::cout << "'3': About Z axis" << std::endl;
        std::cin >> axisPick;
        switch (axisPick)
        {
        case '1':
        {
          BML::Vector3D result = v1.RotateAboutX(angle);
          std::cout << "result: " << result << std::endl;
          break;
        }
        case '2':
        {
          BML::Vector3D result = v1.RotateAboutY(angle);
          std::cout << "result: " << result << std::endl;
          break;
        }
        case '3':
        {
          BML::Vector3D result = v1.RotateAboutZ(angle);
          std::cout << "result: " << result << std::endl;
          break;
        }
        default:
          std::cin.clear();
          std::cin.ignore(INT_MAX, '\n');
          break;
        }
        break;
      }
      case '2':
      {
        std::cout << "You picked get magnitude :" << std::endl;

        std::cout << "magnitude: " << v1.GetMagnitude() << std::endl;
        break;
      }
      case '3':
      {
        std::cout << "You picked normalize it :" << std::endl;
        v1.Normalize();
        std::cout << "Normalized: " << v1 << std::endl;
        break;
      }
      case '4':
      {
        std::cout << "You picked dot product computation ! Now, Enter a second vector:" << std::endl;
        std::cin >> x >> y, z;
        BML::Vector3D v2(x, y, z);
        float result = BML::StaticFunctions::Dot(v1, v2);
        std::cout << "result: " << result << std::endl;
        break;
      }
      case '5':
      {
        std::cout << "You picked angle between 2 vectors ! Now, Enter a second vector:" << std::endl;
        std::cin >> x >> y >> z;
        BML::Vector3D v2(x, y, z);
        float result = BML::StaticFunctions::Angle(v1, v2);
        std::cout << "result (in radians): " << result << std::endl;
        std::cout << "result (in degrees): " << result * 180.0f / PI << std::endl;
        break;
      }
      case '6':
      {
        std::cout << "You picked lerp computation ! Now, Enter a second vector to lerp to:" << std::endl;
        std::cin >> x >> y >> z;
        BML::Vector3D v2(x, y, z);
        float percent = 0.0f;
        std::cout << "Enter the speed of the lerp (0 to 1) " << std::endl;
        std::cin >> percent;
        std::cout << v1 << std::endl;
        while (v1 != v2)
        {
          v1 = BML::StaticFunctions::Lerp(v1, v2, percent);
          std::cout << v1 << std::endl;
        }
        break;
      }
      case '7':
      {
        std::cout << "You picked distance between 2 vectors ! Now, Enter a second vector:" << std::endl;
        std::cin >> x >> y >> z;
        BML::Vector3D v2(x, y, z);
        float result = BML::StaticFunctions::Distance(v1, v2);
        std::cout << "distance: " << result << std::endl;
        break;
      }
      case '8':
      {
        std::cout << "You picked cross product computation! Now, Enter a second vector:" << std::endl;
        std::cin >> x >> y >> z;
        BML::Vector3D v2(x, y, z);
        BML::Vector3D result = BML::StaticFunctions::Cross(v1, v2);
        std::cout << "result: " << result << std::endl;
        break;
      }
      case '9':
      {
        std::cout << "You picked vector reflect computation! Now, Enter a second vector:" << std::endl;
        std::cin >> x >> y >> z;
        BML::Vector3D v2(x, y, z);
        BML::Vector3D result = BML::StaticFunctions::Reflect(v1, v2);
        std::cout << "result: " << result << std::endl;
        break;
      }
      default:
        std::cin.clear();
        std::cin.ignore(INT_MAX, '\n');
        break;
      }
      system("Pause");
      system("CLS");
      break;
    }
    case '3':
    {
      float x, y, z, w;
      std::cout << "enter x, y, z and w values for the vector: " << std::endl;
      std::cin >> x >> y >> z >> w;
      BML::Vector4D v1(x, y, z, w);
      std::cout << v1 << std::endl;
      std::cout << "What do you want to do with this vector ?" << std::endl;
      char choice;
      std::cout << "Options: " << std::endl;
      std::cout << "'+': Compute addition" << std::endl;
      std::cout << "'-': Compute subtraction" << std::endl;
      std::cout << "'*': Compute multiplication" << std::endl;
      std::cout << "'/': Compute division" << std::endl;
      std::cout << "'1': Compute rotation" << std::endl;
      std::cout << "'2': Get Magnitude" << std::endl;
      std::cout << "'3': Normalize it" << std::endl;
      std::cout << "'4': Compute dot product" << std::endl;
      std::cout << "'5': Get angle between this and other vector" << std::endl;
      std::cout << "'6': Compute Lerp" << std::endl;
      std::cout << "'7': Get distance between this and other vector" << std::endl;
      std::cout << "'8': Compute cross product" << std::endl;
      std::cout << "'9': Compute vector reflect" << std::endl;

      std::cin >> choice;
      switch (choice)
      {
      case '+':
      {
        std::cout << "You picked addition ! Now, Enter a second vector:" << std::endl;
        std::cin >> x >> y >> z >> w;
        BML::Vector4D v2(x, y, z, w);
        BML::Vector4D result = v1 + v2;
        std::cout << "result: " << result << std::endl;
        break;
      }
      case '-':
      {
        std::cout << "You picked subtraction ! Now, Enter a second vector:" << std::endl;
        std::cin >> x >> y >> z >> w;
        BML::Vector4D v2(x, y, z, w);
        BML::Vector4D result = v1 - v2;
        std::cout << "result: " << result << std::endl;
        break;
      }
      case '*':
      {
        float scalar;
        std::cout << "You picked multiplication ! Now, Enter a scalar to multiply with:" << std::endl;
        std::cin >> scalar;
        BML::Vector4D result = v1 * scalar;
        std::cout << "result: " << result << std::endl;
        break;
      }
      case '/':
      {
        float scalar;
        std::cout << "You picked division ! Now, Enter a scalar to divide with:" << std::endl;
        std::cin >> scalar;
        BML::Vector4D result = v1 / scalar;
        std::cout << "result: " << result << std::endl;
        break;
      }
      case '1':
      {
        float angle = 0.0f;
        std::cout << "You picked rotation ! Now, Enter your required angle of rotation (in degrees):" << std::endl;
        std::cin >> angle;
        char axisPick;
        std::cout << "About which axis do you want to rotate ?" << std::endl;
        std::cout << "'1': About X axis" << std::endl;
        std::cout << "'2': About Y axis" << std::endl;
        std::cout << "'3': About Z axis" << std::endl;
        std::cin >> axisPick;
        switch (axisPick)
        {
        case '1':
        {
          BML::Matrix4x4 rot;
          rot.ConvertForRotationX(angle);
          BML::Vector4D result = rot * v1;
          std::cout << "result: " << result << std::endl;
          break;
        }
        case '2':
        {
          BML::Matrix4x4 rot;
          rot.ConvertForRotationY(angle);
          BML::Vector4D result = rot * v1;
          std::cout << "result: " << result << std::endl;
          break;
        }
        case '3':
        {
          BML::Matrix4x4 rot;
          rot.ConvertForRotationZ(angle);
          BML::Vector4D result = rot * v1;
          std::cout << "result: " << result << std::endl;
          break;
        }
        default:
          std::cin.clear();
          std::cin.ignore(INT_MAX, '\n');
          break;
        }
        break;
      }
      case '2':
      {
        std::cout << "You picked get magnitude :" << std::endl;

        std::cout << "magnitude: " << v1.GetMagnitude() << std::endl;
        break;
      }
      case '3':
      {
        std::cout << "You picked normalize it :" << std::endl;
        v1.Normalize();
        std::cout << "Normalized: " << v1 << std::endl;
        break;
      }
      case '4':
      {
        std::cout << "You picked dot product computation ! Now, Enter a second vector:" << std::endl;
        std::cin >> x >> y >> z >> w;
        BML::Vector4D v2(x, y, z, w);
        float result = BML::StaticFunctions::Dot(v1, v2);
        std::cout << "result: " << result << std::endl;
        break;
      }
      case '5':
      {
        std::cout << "You picked angle between 2 vectors ! Now, Enter a second vector:" << std::endl;
        std::cin >> x >> y >> z >> w;
        BML::Vector4D v2(x, y, z, w);
        float result = BML::StaticFunctions::Angle(v1, v2);
        std::cout << "result (in radians): " << result << std::endl;
        std::cout << "result (in degrees): " << result * 180.0f / PI << std::endl;
        break;
      }
      case '6':
      {
        std::cout << "You picked lerp computation ! Now, Enter a second vector to lerp to:" << std::endl;
        std::cin >> x >> y >> z >> w;
        BML::Vector4D v2(x, y, z, w);
        float percent = 0.0f;
        std::cout << "Enter the speed of the lerp (0 to 1) " << std::endl;
        std::cin >> percent;
        std::cout << v1 << std::endl;
        while (v1 != v2)
        {
          v1 = BML::StaticFunctions::Lerp(v1, v2, percent);
          std::cout << v1 << std::endl;
        }
        break;
      }
      case '7':
      {
        std::cout << "You picked distance between 2 vectors ! Now, Enter a second vector:" << std::endl;
        std::cin >> x >> y >> z >> w;
        BML::Vector4D v2(x, y, z, w);
        float result = BML::StaticFunctions::Distance(v1, v2);
        std::cout << "distance: " << result << std::endl;
        break;
      }
      case '8':
      {
        std::cout << "You picked cross product computation! Now, Enter a second vector:" << std::endl;
        std::cin >> x >> y >> z >> w;
        BML::Vector4D v2(x, y, z, w);
        BML::Vector4D result = BML::StaticFunctions::Cross(v1, v2);
        std::cout << "result: " << result << std::endl;
        break;
      }
      case '9':
      {
        std::cout << "You picked vector reflect computation! Now, Enter a second vector:" << std::endl;
        std::cin >> x >> y >> z >> w;
        BML::Vector4D v2(x, y, z, w);
        BML::Vector4D result = BML::StaticFunctions::Reflect(v1, v2);
        std::cout << "result: " << result << std::endl;
        break;
      }
      default:
        std::cin.clear();
        std::cin.ignore(INT_MAX, '\n');
        break;
      }
      system("Pause");
      system("CLS");
      break;
    }
    case '4':
    {
      BML::Matrix4x4 mat;
      std::cout << "Enter 16 values for the matrix" << std::endl;
      for (int i = 0; i < 4; i++)
      {
        for (int j = 0; j < 4; j++)
        {
          std::cin >> mat.m_matrix[i][j];
        }
      }
      std::cout << mat << std::endl;
      std::cout << "What do you want to do with this matrix ?" << std::endl;
      char choice;
      std::cout << "Options: " << std::endl;
      std::cout << "'+': Compute addition" << std::endl;
      std::cout << "'-': Compute subtraction" << std::endl;
      std::cout << "'*': Compute multiplication" << std::endl;
      std::cout << "'/': Compute division" << std::endl;
      std::cout << "'1': Convert for scaling" << std::endl;
      std::cout << "'2': Convert for translation" << std::endl;
      std::cout << "'3': Convert for rotation" << std::endl;
      std::cout << "'4': Convert to ortho matrix" << std::endl;
      std::cout << "'5': Convert to perspective matrix" << std::endl;
      std::cout << "'6': Get the determinant of a matrix" << std::endl;
      std::cout << "'7': Invert a matrix" << std::endl;
      std::cout << "'8': Get the quaternion representation of a matrix" << std::endl;
      std::cout << "'9': Convert to a LookAt Matrix" << std::endl;

      std::cin >> choice;
      switch (choice)
      {
      case '+':
      {
        std::cout << "You picked addition ! Now, enter the values for the second matrix:" << std::endl;
        BML::Matrix4x4 mat2;
        for (int i = 0; i < 4; i++)
        {
          for (int j = 0; j < 4; j++)
          {
            std::cin >> mat2.m_matrix[i][j];
          }
        }
        BML::Matrix4x4 result = mat + mat2;
        std::cout << "result: " << std::endl;
        std::cout << result << std::endl;
        break;
      }
      case '-':
      {
        std::cout << "You picked subtraction ! Now, enter the values for the second matrix:" << std::endl;
        BML::Matrix4x4 mat2;
        for (int i = 0; i < 4; i++)
        {
          for (int j = 0; j < 4; j++)
          {
            std::cin >> mat2.m_matrix[i][j];
          }
        }
        BML::Matrix4x4 result = mat - mat2;
        std::cout << "result: " << std::endl;
        std::cout << result << std::endl;
        break;
      }
      case '*':
      {
        std::cout << "You picked multiplication ! Now, choose what multiplication you want:" << std::endl;
        std::cout << "'1': Matrix x Matrix multiplication" << std::endl;
        std::cout << "'2': Matrix x Vector multiplication" << std::endl;
        std::cout << "'3': Matrix x Scalar multiplication" << std::endl;
        char pick;
        std::cin >> pick;
        switch (pick)
        {
        case '1':
        {
          std::cout << "Enter the 16 values for the second matrix" << std::endl;
          BML::Matrix4x4 mat2;
          for (int i = 0; i < 4; i++)
          {
            for (int j = 0; j < 4; j++)
            {
              std::cin >> mat2.m_matrix[i][j];
            }
          }
          BML::Matrix4x4 result = mat + mat2;
          std::cout << "result: " << std::endl;
          std::cout << result << std::endl;
          break;
        }
        case '2':
        {
          float x, y, z, w;
          std::cout << "Enter the 4 values for the 4D homogenous vector" << std::endl;
          std::cin >> x >> y >> z >> w;
          BML::Vector4D hVec(x, y, z, w);
          BML::Vector4D result = mat * hVec;
          std::cout << "Result: " << result << std::endl;
          break;
        }
        case '3':
        {
          float scalar;
          std::cout << "Enter your scalar: " << std::endl;
          std::cin >> scalar;
          BML::Matrix4x4 result = mat * scalar;
          std::cout << "result: " << std::endl;
          std::cout << result << std::endl;
          break;
        }
        default:
          std::cin.clear();
          std::cin.ignore(INT_MAX, '\n');
          break;
        }

        break;
      }
      case '/':
      {
        float scalar;
        std::cout << "You picked division ! Now, enter your scalar:" << std::endl;
        std::cin >> scalar;
        BML::Matrix4x4 result = mat / scalar;
        std::cout << "result: " << std::endl;
        std::cout << result << std::endl;
        break;
      }
      case '1':
      {
        float x, y, z;
        std::cout << "Enter the 3 scale values" << std::endl;
        std::cin >> x >> y >> z;
        mat.ConvertForScaling(x, y, z);
        std::cout << "result: " << std::endl;
        std::cout << mat << std::endl;
        break;
      }
      case '2':
      {
        float x, y, z;
        std::cout << "Enter the 3 translation values" << std::endl;
        std::cin >> x >> y >> z;
        mat.ConvertForTranslation(x, y, z);
        std::cout << "result: " << std::endl;
        std::cout << mat << std::endl;
        break;
      }
      case '3':
      {
        float angle = 0.0f;
        std::cout << "You picked rotation ! Now, Enter your required angle of rotation (in degrees):" << std::endl;
        std::cin >> angle;
        char axisPick;
        std::cout << "About which axis do you want to convert ?" << std::endl;
        std::cout << "'1': Convert for Rotation about X" << std::endl;
        std::cout << "'2': Convert for Rotation about Y" << std::endl;
        std::cout << "'3': Convert for Rotation about Z" << std::endl;
        std::cout << "'4': Rotate about every axis (requires new values)" << std::endl;

        std::cin >> axisPick;
        switch (axisPick)
        {
        case '1':
        {
          mat.ConvertForRotationX(angle);
          std::cout << "result: " << std::endl;
          std::cout << mat << std::endl;
          break;
        }
        case '2':
        {
          mat.ConvertForRotationY(angle);
          std::cout << "result: " << std::endl;
          std::cout << mat << std::endl;
          break;
        }
        case '3':
        {
          mat.ConvertForRotationZ(angle);
          std::cout << "result: " << std::endl;
          std::cout << mat << std::endl;
          break;
        }
        case '4':
        {
          std::cout << "Enter the x, y, z angles for rotation (in degrees):" << std::endl;
          float x, y, z;
          std::cin >> x >> y >> z;
          mat.ConvertForRotation(x, y, z);
          std::cout << "result: " << std::endl;
          std::cout << mat << std::endl;
          break;
        }
        default:
          std::cin.clear();
          std::cin.ignore(INT_MAX, '\n');
          break;
        }
        break;
      }
      case '4':
      {
        float left, right, bottom, top, near, far;
        std::cout << "Enter the left, right, bottom, top, near, far values for the ortho matrix(in this order): " << std::endl;
        std::cin >> left >> right >> bottom >> top >> near >> far;
        mat.Ortho(left, right, bottom, top, near, far);
        std::cout << "result: " << std::endl;
        std::cout << mat << std::endl;
        break;
      }
      case '5':
      {
        float fov, aspect, near, far;
        std::cout << "Enter the FoV, aspect, near, far values for the Projection matrix(in this order): " << std::endl;
        std::cin >> fov >> aspect >> near >> far;
        mat.Perspective(fov, aspect, near, far);
        std::cout << "result: " << std::endl;
        std::cout << mat << std::endl;
        break;
      }
      case '6':
      {
        std::cout << "determinant: " << mat.GetDeterminant() << std::endl;
        break;
      }
      case '7':
      {
        std::cout << "Inverted Matrix:" << std::endl;
        mat.Invert();
        std::cout << mat << std::endl;
        break;
      }
      case '8':
      {
        BML::Quaternion quat = mat.GetQuaternion4D();
        std::cout << "quaternion representation of the matrix: " << std::endl;
        std::cout << quat << std::endl;
        break;
      }
      case '9':
      {
        BML::Vector3D eye;
        BML::Vector3D center;
        BML::Vector3D up(0.0f, 1.0f, 0.0f);
        std::cout << "You chose a lookat matrix!" << std::endl;
        std::cout << "You will need to enter 2 vectors" << std::endl;
        std::cout << "enter values for the eye (camera position)" << std::endl;
        std::cin >> eye.m_x >> eye.m_y >> eye.m_z;
        std::cout << "enter values for the center (origin point to look at)" << std::endl;
        std::cin >> center.m_x >> center.m_y >> center.m_z;
        BML::Matrix4x4 result;
        result.LookAt(eye, center, up);
        std::cout << "result: " << std::endl;
        std::cout << result << std::endl;
        break;
      }
      default:
        std::cin.clear();
        std::cin.ignore(INT_MAX, '\n');
        break;
      }
      system("Pause");
      system("CLS");
      break;
    }
    case '5':
    {
      float x, y, z;
      std::cout << "enter x, y, z euler angle values (in degrees) that will be converted to a quaternion: " << std::endl;
      std::cin >> x >> y >> z;
      BML::Quaternion quat = BML::StaticFunctions::Euler(x, y, z);
      std::cout << quat << std::endl;
      std::cout << "What do you want to do with this quaternion ?" << std::endl;
      char choice;
      std::cout << "Options: " << std::endl;
      std::cout << "'+': Compute addition" << std::endl;
      std::cout << "'-': Compute subtraction" << std::endl;
      std::cout << "'*': Compute multiplication" << std::endl;
      std::cout << "'/': Compute division" << std::endl;
      std::cout << "'1': Conjugate the quat" << std::endl;
      std::cout << "'2': Inverse the quat" << std::endl;
      std::cout << "'3': Normalize the quat" << std::endl;
      std::cout << "'4': Get the euler angle representation" << std::endl;
      std::cout << "'5': Get the 4x4 matrix representation" << std::endl;
      std::cout << "'6': Dot product computation" << std::endl;
      std::cout << "'7': Get the angle between 2 quaternions" << std::endl;
      std::cout << "'8': Convert to identity quaternion" << std::endl;
      std::cout << "'9': Get the magnitude of the quaternion" << std::endl;

      std::cin >> choice;
      switch (choice)
      {
      case '+':
      {
        std::cout << "You picked addition !  Now, enter another 3 euler angle values for the second quaternion:" << std::endl;
        std::cin >> x >> y >> z;
        BML::Quaternion q2 = BML::StaticFunctions::Euler(x, y, z);
        BML::Quaternion result = quat + q2;
        std::cout << "result: " << result << std::endl;
        break;
      }
      case '-':
      {
        std::cout << "You picked addition ! Now, enter another 3 euler angle values for the second quaternion:" << std::endl;
        std::cin >> x >> y >> z;
        BML::Quaternion q2 = BML::StaticFunctions::Euler(x, y, z);
        BML::Quaternion result = quat - q2;
        std::cout << "result: " << result << std::endl;
        break;
      }
      case '*':
      {
        std::cout << "Choose between these 2:" << std::endl;
        std::cout << "'1': Quat x Quat multiplication" << std::endl;
        std::cout << "'2': Quat x Scalar multiplication" << std::endl;
        char pick;
        std::cin >> pick;
        switch (pick)
        {
        case '1':
        {
          std::cout << "Great! Now, enter another 3 euler angle values for the second quaternion:" << std::endl;
          std::cin >> x >> y >> z;
          BML::Quaternion q2 = BML::StaticFunctions::Euler(x, y, z);
          BML::Quaternion result = quat * q2;
          std::cout << "result: " << result << std::endl;
          break;
        }
        case '2':
        {
          std::cout << "Great, now enter the scalar" << std::endl;
          float scalar;
          std::cin >> scalar;
          BML::Quaternion result = quat * scalar;
          break;
        }
        default:
          std::cin.clear();
          std::cin.ignore(INT_MAX, '\n');
          break;
        }
        break;
      }
      case '/':
      {
        std::cout << "Choose between these 2:" << std::endl;
        std::cout << "'1': Quat x Quat division" << std::endl;
        std::cout << "'2': Quat x Scalar division" << std::endl;
        char pick;
        std::cin >> pick;
        switch (pick)
        {
        case '1':
        {
          std::cout << "Great! Now, enter another 3 euler angle values for the second quaternion:" << std::endl;
          std::cin >> x >> y >> z;
          BML::Quaternion q2 = BML::StaticFunctions::Euler(x, y, z);
          BML::Quaternion result = quat / q2;
          std::cout << "result: " << result << std::endl;
          break;
        }
        case '2':
        {
          std::cout << "Great, now enter the scalar" << std::endl;
          float scalar;
          std::cin >> scalar;
          BML::Quaternion result = quat / scalar;
          break;
        }
        default:
          std::cin.clear();
          std::cin.ignore(INT_MAX, '\n');
          break;
        }
        break;
      }
      case '1':
      {
        quat.Conjugate();
        std::cout << "Conjugated quat: " << quat << std::endl;
        break;
      }
      case '2':
      {
        quat.Inverse();
        std::cout << "Inversed quat: " << quat << std::endl;
        break;
      }
      case '3':
      {
        quat.Normalize();
        std::cout << "Normalized quat: " << quat << std::endl;
        break;
      }
      case '4':
      {
        BML::Vector3D eulerAngles = quat.GetEulerAngles();
        std::cout << "Euler angles: " << eulerAngles << std::endl;
        break;
      }
      case '5':
      {
        BML::Matrix4x4 quatToMat = quat.GetMatrix4D();
        std::cout << "Matrix representation: " << std::endl;
        std::cout << quatToMat << std::endl;
        break;
      }
      case '6':
      {
        std::cout << "Great! Now, enter another 3 euler angle values for the second quaternion:" << std::endl;
        std::cin >> x >> y >> z;
        BML::Quaternion q2 = BML::StaticFunctions::Euler(x, y, z);
        float result = BML::StaticFunctions::Dot(quat, q2);
        std::cout << "result: " << result << std::endl;
        break;
      }
      case '7':
      {
        std::cout << "Great! Now, enter another 3 euler angle values for the second quaternion:" << std::endl;
        std::cin >> x >> y >> z;
        BML::Quaternion q2 = BML::StaticFunctions::Euler(x, y, z);
        float angle = BML::StaticFunctions::Angle(quat, q2);
        std::cout << "result (in radians): " << angle << std::endl;
        std::cout << "result (in degrees): " << angle * 180.0f / PI << std::endl;
        break;
      }
      case '8':
      {
        quat.MakeIdentity();
        std::cout << "result: " << quat << std::endl;
        break;
      }
      case '9':
      {
        std::cout << "magnitude: " << quat.GetMagnitude() << std::endl;
        break;
      }
      default:
        std::cin.clear();
        std::cin.ignore(INT_MAX, '\n');
        break;
      }
      system("Pause");
      system("CLS");
      break;
    }
    default:
      system("CLS");
      std::cin.clear();
      std::cin.ignore(INT_MAX, '\n');
      break;
    }
  }
  return 0;
}