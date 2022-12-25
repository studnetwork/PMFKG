import { Injectable } from '@angular/core';
import { ActivatedRouteSnapshot, CanActivate, Router, RouterStateSnapshot, UrlTree } from '@angular/router';
import { Observable, of } from 'rxjs';
import { CookieService } from 'ngx-cookie-service';
import { AuthService } from '../../services/auth/auth.service';

/**
 * Kreirano sa: `ng g g guards/auth/auth`
 */
@Injectable({
  providedIn: 'root'
})
export class AuthGuard implements CanActivate {

  constructor(
    private cookie: CookieService, 
    private auth: AuthService,
    private router: Router) {}

  canActivate(
    route: ActivatedRouteSnapshot,
    state: RouterStateSnapshot): Observable<boolean | UrlTree> | Promise<boolean | UrlTree> | boolean | UrlTree {
    
      let isValid: boolean = false;

      if(this.cookie.check("token")) 
        isValid = this.auth.isJwtValid(this.cookie.get("token"));
      
      if(! isValid)
        this.router.navigate(["/login"]);

      console.log(`is token valid? ${isValid}`)

      return isValid;
  }
  
}
