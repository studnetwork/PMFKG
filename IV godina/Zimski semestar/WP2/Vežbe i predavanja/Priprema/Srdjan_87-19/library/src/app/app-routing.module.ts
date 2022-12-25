import { NgModule } from '@angular/core';
import { RouterModule, Routes } from '@angular/router';
import { BooksComponent } from './components/books/books.component';
import { AuthGuard } from './core/guards/auth/auth.guard';
import { LoginComponent } from './components/auth/login/login.component';
import { PageNotFoundComponent } from './components/page-not-found/page-not-found.component';
import { RegisterComponent } from './components/auth/register/register.component';
import { NewBookComponent } from './components/books/components/new-book/new-book.component';
import { NewAuthorComponent } from './components/authors/components/new-author/new-author.component';
import { AuthorsComponent } from './components/authors/authors.component';

const routes: Routes = [{
  path: "books",
  canActivate: [AuthGuard],
  children: [{ // radilo bi i ako bi path "" bio pre "new"
      path: "new",
      component: NewBookComponent
    }, {
      path: "",
      pathMatch: "full",
      component: BooksComponent
    }
  ]
}, {
  path: "authors",
  canActivate: [AuthGuard],
  children: [{
    path: "new",
    component: NewAuthorComponent
  }, {
    path: "",
    pathMatch: "full",
    component: AuthorsComponent
  }]
}, {
  path: "login",
  component: LoginComponent
}, {
  path: "register",
  component: RegisterComponent
}, {
  path: "",
  redirectTo: "books",
  pathMatch: "full"
}, {
  path: "**",
  component: PageNotFoundComponent
}];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})
export class AppRoutingModule { }
