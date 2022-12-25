import { Component, OnInit } from '@angular/core';
import { Router } from '@angular/router';
import { Jwt } from 'src/app/core/models/jwt.model';
import { AuthService } from '../../../core/services/auth/auth.service';
import { HttpErrorHandlerService } from 'src/app/core/services/error/http-error-handler.service';

/**
 * Kreirano sa: `ng g c components/auth/login`
 */
@Component({
  selector: 'app-login',
  templateUrl: './login.component.html',
  styleUrls: ['./login.component.css']
})
export class LoginComponent implements OnInit {
  email: string = "";
  password: string = "";

  showErrorMsg = false;
  errorMessage = "";

  constructor(
    private authService: AuthService,
    private router: Router,
    private httpErrorHandler: HttpErrorHandlerService) {}
    
  ngOnInit(): void {
    if(this.authService.isLoggedIn())
      this.router.navigateByUrl("/");
  }

  login(): void {
    
    this.authService.login(this.email, this.password).subscribe({
      next: (jwt: Jwt) => {
        this.showErrorMsg = false;
        console.log(`Logovanje je uspesno obavljeno. Dobijen je token: ${jwt.token}`)
        this.authService.saveToken(jwt.token);
        this.router.navigateByUrl("/");
      },
      error: (returnedError) => {
        console.log(`Neuspesno logovanje`)
        this.showErrorMsg = true;

        if(returnedError.status == 400 || returnedError.status == 401) {
          this.errorMessage = "Nevalidni kredencijali. Pokusajte ponovo."
          return;
        }

        this.httpErrorHandler.handle(returnedError)
      }
    });
  }

}
